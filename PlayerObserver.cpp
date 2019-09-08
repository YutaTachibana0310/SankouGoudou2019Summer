//=====================================
//
//�v���C���[�I�u�U�[�o�[����[PlayerObserver.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "PlayerObserver.h"
#include "InputController.h"

#include "PlayerMove.h"
#include "PlayerWait.h"
#include "PlayerReturn.h"
#include "PlayerIdle.h"

#include "GameParticleManager.h"
#include "sound.h"

#include <algorithm>

using namespace std;

/**************************************
�}�N����`
***************************************/
#define MOVETARGET_DEFAULT	(99)

/**************************************
�\���̒�`
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
PlayerObserver::PlayerObserver()
{
	player = new Player();
	model = new PlayerModel();
	trailEffect = new PlayerTrail();
	bomberController = new PlayerBomberController();
	bulletController = new PlayerBulletController();

	fsm[PlayerState::Idle] = new PlayerIdle();
	fsm[PlayerState::Wait] = new PlayerWait();
	fsm[PlayerState::Move] = new PlayerMove();
	fsm[PlayerState::Return] = new PlayerReturn();

	//�ړ���m��
	targetPos.resize(5);
	for (UINT i = 0; i < targetPos.size(); i++)
	{
		targetPos[i] = LineTrailModel::GetEdgePos(i);
	}

	//moveTarget������
	moveTarget = MOVETARGET_DEFAULT;

	//���W�b�N�X�V�L����
	enableUpdateLogic = true;
}

/**************************************
�f�X�g���N�^
***************************************/
PlayerObserver::~PlayerObserver()
{
	SAFE_DELETE(player);
	SAFE_DELETE(model);
	SAFE_DELETE(trailEffect);

	SAFE_DELETE(bomberController);
	SAFE_DELETE(bulletController);
}

/**************************************
����������
***************************************/
void PlayerObserver::Init()
{
	player->Init();
	ChangeStatePlayer(PlayerState::Idle);
}

/**************************************
�I������
***************************************/
void PlayerObserver::Uninit()
{
	player->Uninit();

	bomberController->Uninit();
	bulletController->Uninit();
}

/**************************************
�X�V����
***************************************/
void PlayerObserver::Update()
{
	if (enableUpdateLogic)
	{
		int stateResult = player->Update();

		if (stateResult != STATE_CONTINUOUS)
			OnPlayerStateFinish();

		bulletController->Update();
	}

	trailEffect->Update();

	bomberController->Update();

	player->Animation();
}

/**************************************
�`�揈��
***************************************/
void PlayerObserver::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	player->Draw();

	trailEffect->Draw();

	bomberController->Draw();
	bulletController->Draw();
}

/**************************************
���͊m�F����
***************************************/
void PlayerObserver::CheckInput()
{
	//���͊Ԋu���J�E���g
	player->inputInterval++;

	//���͂��m�F
	int inputID = GetMoveInput();

	const int InvalidInput = 5;
	if(inputID < InvalidInput)
		PushInput(inputID);
}

/**************************************
���͏���
***************************************/
void PlayerObserver::PushInput(int num)
{
	//�����Ƃ���ւ͈ړ����Ȃ�
	if (num == moveTarget)
		return;

	//�v���C���[�̓��͊Ԋu�����Z�b�g
	player->inputInterval = 0;

	//Wait��Ԃł����Move�ɑJ��
	if (current == PlayerState::Wait || current == PlayerState::Idle)
	{
		if (current == PlayerState::Wait)
		{
			//���G��ԂłȂ���Γ����蔻���L����
			if (!player->flgInvincible)
			{
				player->collider->active = true;
				player->collider->SetTrailIndex(LineTrailModel(moveTarget, num));
			}

			player->ChangeAnim(PlayerAnimID::Attack);
			trailEffect->Init(&player->transform.pos);
		}

		moveTarget = num;
		player->goalpos = targetPos[moveTarget];
		ChangeStatePlayer(PlayerState::Move);
	}
	//��s���͂�ۑ����ĉ������Ȃ�
	else
	{
		model->PushInput(num);
	}
}

/**************************************
Player��ԑJ��
***************************************/
void PlayerObserver::ChangeStatePlayer(PlayerState next)
{
	prevState = current;
	current = next;
	player->ChangeState(fsm[current]);
}

/**************************************
�v���C���[�̏�ԏI�����̏���
***************************************/
void PlayerObserver::OnPlayerStateFinish()
{
	switch (current)
	{
	case PlayerState::Move:
		OnFinishPlayerMove();
		break;

	case PlayerState::Wait:
		OnFinishPlayerWait();
		break;

	case PlayerState::Return:
		OnFinishPlayerReturn();
		break;

	}
}
/**************************************
Move�R�[���o�b�N
***************************************/
void PlayerObserver::OnFinishPlayerMove()
{
	//�����蔻��𖳌���
	player->collider->active = true;

	//�ړ��������v�b�V���i�{���o�[�̃X�g�b�N�C���^�[�o�����I�����Ă�����j
	model->PushMoveStack(moveTarget, bomberController->CanStock());

	//�g���C�����I��
	trailEffect->Uninit();

	//Wait����Move����̈ړ��ł���΃o���b�g����
	if (prevState == PlayerState::Wait || prevState == PlayerState::Move)
	{
		LineTrailModel modelTrail;
		model->GetPlayerTrail(&modelTrail);
		bulletController->SetPlayerBullet(modelTrail);
	}

	//�{���o�[�X�g�b�N�\����M��������������������
	TryStockBomber();

	//��s���͊m�F
	int prevMoveTarget = moveTarget;
	if (model->IsExistPrecedInput(&moveTarget))
	{
		//�����蔻����X�V
		player->collider->SetTrailIndex(LineTrailModel(prevMoveTarget, moveTarget));

		player->goalpos = targetPos[moveTarget];
		trailEffect->Init(&player->transform.pos);
		player->ChangeAnim(PlayerAnimID::Attack);
		ChangeStatePlayer(PlayerState::Move);
	}
	//������Αҋ@��Ԃ֑J��
	else
	{
		player->ChangeAnim(PlayerAnimID::Flying);
		ChangeStatePlayer(PlayerState::Wait);
	}
}

/**************************************
Wait�R�[���o�b�N
***************************************/
void PlayerObserver::OnFinishPlayerWait()
{
	//TODO:�����ʒu�ɖ߂�̂ŐF�X���Z�b�g
	model->Clear();
	moveTarget = MOVETARGET_DEFAULT;
	player->EnableCollider(false);

	//Return��Ԃ֑J�ڂ������ʒu��
	ChangeStatePlayer(PlayerState::Return);
}

/**************************************
Return�R�[���o�b�N
***************************************/
void PlayerObserver::OnFinishPlayerReturn()
{
	//�v���C���[��Idle��Ԃ֑J��
	ChangeStatePlayer(PlayerState::Idle);
}

/**************************************
�{���o�[�V�[�P���X�J�n����
***************************************/
void PlayerObserver::OnStartBomberSequence()
{
	//�{���o�[SE
	Sound::GetInstance()->SetPlaySE(BOMB, true, (Sound::GetInstance()->changevol / 5.0f));
	enableUpdateLogic = false;
	player->ChangeAnim(PlayerAnimID::FireBomber);
	player->ChargeBomber();
}

/**************************************
�{���o�[�V�[�P���X�I������
***************************************/
void PlayerObserver::OnFinishBomberSequence()
{
	enableUpdateLogic = true;

	//��s���͊m�F
	if (model->IsExistPrecedInput(&moveTarget))
	{
		player->goalpos = targetPos[moveTarget];
		trailEffect->Init(&player->transform.pos);
		player->ChangeAnim(PlayerAnimID::Attack);
		ChangeStatePlayer(PlayerState::Move);
	}
	//������Αҋ@��Ԃ֑J��
	else
	{
		player->ChangeAnim(PlayerAnimID::Flying);
		ChangeStatePlayer(PlayerState::Wait);
	}
}

/**************************************
�{���o�[���˔���
***************************************/
bool PlayerObserver::ShouldFireBomber()
{
	//�{���o�[�̃X�g�b�N���Ȃ����false
	if (!bomberController->CanSet())
		return false;

	//���˂̓��͂��s���Ă��Ȃ����false
	if (!GetBomberInput())
		return false;

	return true;
}

/**************************************
�{���o�[���ˏ���
***************************************/
void PlayerObserver::FirePlayerBomber(std::list<std::shared_ptr<Enemy>>& targetList)
{
	if (bomberController->CanSet())
		bomberController->SetPlayerBomber(targetList, player->transform.pos);
}

/**************************************
�{���o�[���ˏ���
***************************************/
void PlayerObserver::FirePlayerBomber(std::shared_ptr<BossEnemyModel>& targetList)
{
	if (bomberController->CanSet())
		bomberController->SetPlayerBomber(targetList, player->transform.pos);
}

/**************************************
�{���o�[���ˏ���
***************************************/
void  PlayerObserver::FirePlayerBomber(std::list<std::shared_ptr<RebarObstacle>>& targetList)
{
	if (bomberController->CanSet())
		bomberController->SetPlayerBomber(targetList, player->transform.pos);
}

/**************************************
�������o����
***************************************/
void PlayerObserver::OnStartAccel()
{
	const D3DXVECTOR3 EffectPos = D3DXVECTOR3(0.0f, 10.0f, 50.0f);
	GameParticleManager::Instance()->SetAccelEffect(&(player->transform.pos + EffectPos));
}

/**************************************
�{���o�[�X�g�b�N����
***************************************/
void PlayerObserver::TryStockBomber()
{
	//�X�g�b�N�C���^�[�o�����o�߂��Ă��邩
	if (!bomberController->CanStock())
		return;

	//��M�������������Ă��邩
	if (!model->CheckOneStroke())
		return;

	//�{���o�[���X�g�b�N
	bomberController->AddStock();

	//�G�t�F�N�g�Đ�
	player->StockBomber();

}

/**************************************
PlayerTransform�擾����
***************************************/
const Transform& PlayerObserver::GetPlayerTransform() const
{
	return player->transform;
}

/**************************************
HP�擾����
***************************************/
float PlayerObserver::GetHpPercent()
{
	return player->GetHp() / Player::MaxHp;
}

/**************************************
��������
***************************************/
bool PlayerObserver::IsAlive()
{
	return player->IsAlive();
}