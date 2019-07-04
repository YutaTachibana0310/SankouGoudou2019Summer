//=====================================
//
//�v���C���[�I�u�U�[�o�[����[PlayerObserver.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "PlayerObserver.h"

#include "PlayerMove.h"
#include "PlayerWait.h"
#include "PlayerReturn.h"
#include "PlayerIdle.h"
#include "PlayerBomber.h"

#include <algorithm>

using namespace std;

/**************************************
�}�N����`
***************************************/
#define MOVETARGET_DEFAULT	(99)

/**************************************
�\���̒�`
***************************************/


PlayerBomber *bomber;

/**************************************
�R���X�g���N�^
***************************************/
PlayerObserver::PlayerObserver()
{
	player = new Player();
	model = new PlayerModel();
	trailEffect = new PlayerTrail();
	bomber = new PlayerBomber();

	fsm[PlayerState::Idle] = new PlayerIdle();
	fsm[PlayerState::Wait] = new PlayerWait();
	fsm[PlayerState::Move] = new PlayerMove();
	fsm[PlayerState::Return] = new PlayerReturn();

	//�ړ���m��
	targetPos.resize(5);

	//moveTarget������
	moveTarget = MOVETARGET_DEFAULT;
}

/**************************************
�f�X�g���N�^
***************************************/
PlayerObserver::~PlayerObserver()
{
	SAFE_DELETE(player);
	SAFE_DELETE(model);
	SAFE_DELETE(trailEffect);

	for (PlayerBullet* bullet : bulletContainer)
	{
		SAFE_DELETE(bullet);
	}
	bulletContainer.clear();

	for (auto stateMachine : fsm)
	{
		SAFE_DELETE(stateMachine.second);
	}
	fsm.clear();
}

/**************************************
����������
***************************************/
void PlayerObserver::Init()
{
	player->Init();
	for (PlayerBullet *bullet : bulletContainer)
	{
		bullet->Init();

	}


	ChangeStatePlayer(PlayerState::Idle);
}

/**************************************
�I������
***************************************/
void PlayerObserver::Uninit()
{
	player->Uninit();
	for (PlayerBullet *bullet : bulletContainer)
	{
		bullet->Uninit();
	}
	
	bomber->Uninit();
	
}

/**************************************
�X�V����
***************************************/
void PlayerObserver::Update()
{
	int stateResult = player->Update();

	if (stateResult != STATE_CONTINUOUS)
		OnPlayerStateFinish();

	for (PlayerBullet *bullet : bulletContainer)
	{
		bullet->Update();
	}

	if (bomber->active)
	{
		bomber->Update();
	}
	trailEffect->Update();
}

/**************************************
�`�揈��
***************************************/
void PlayerObserver::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	player->Draw();

	trailEffect->Draw();

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	pDevice->SetRenderState(D3DRS_LIGHTING, false);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

	for (PlayerBullet *bullet : bulletContainer)
	{
		bullet->Draw();
	}
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	pDevice->SetRenderState(D3DRS_LIGHTING, true);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
	
	bomber->Draw();
	
}

/**************************************
�o���b�g���ˏ���
***************************************/
void PlayerObserver::SetPlayerBullet(PlayerTrailModel trail)
{
	auto itr = find_if(bulletContainer.begin(), bulletContainer.end(), [](PlayerBullet* bullet)
	{
		return !bullet->active;
	});

	if (itr != bulletContainer.end())
	{
		(*itr)->SetTrailIndex((TrailIndex)trail.start, (TrailIndex)trail.end);
		(*itr)->SetEdgePos(&targetPos[trail.start], &targetPos[trail.end]);
		(*itr)->Init();
	}
	else
	{
		PlayerBullet *bullet = new PlayerBullet();
		bullet->SetTrailIndex((TrailIndex)trail.start, (TrailIndex)trail.end);
		bullet->SetEdgePos(&targetPos[trail.start], &targetPos[trail.end]);
		bullet->Init();
		bulletContainer.push_back(bullet);
	}
}

/**************************************
���͏���
***************************************/
void PlayerObserver::PushInput(int num)
{
	//�����Ƃ���ւ͈ړ����Ȃ�
	if (num == moveTarget)
		return;

	//Wait��Ԃł����Move�ɑJ��
	if (current == PlayerState::Wait || current == PlayerState::Idle)
	{
		if(current == PlayerState::Wait)
			trailEffect->Init(&player->transform.pos);

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
�ړ��ڕW�ݒ�
***************************************/
void PlayerObserver::SetMoveTargetPosition(int i, D3DXVECTOR3 pos)
{
	targetPos[i] = pos;
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
	//�ړ��������v�b�V��
	model->PushMoveStack(moveTarget);

	//�g���C�����I��
	trailEffect->Uninit();

	//Wait����Move����̈ړ��ł���΃o���b�g����
	if (prevState == PlayerState::Wait || prevState == PlayerState::Move)
	{
		PlayerTrailModel modelTrail;
		model->GetPlayerTrail(&modelTrail);
		SetPlayerBullet(modelTrail);

	}

	//��M��������
	if (model->CheckOneStroke())
	{
		//�{������
		bomber->SetBomber(&player->bompos,player->transform.pos);
	}

	//��s���͊m�F
	if (model->IsExistPrecedInput(&moveTarget))
	{
		player->goalpos = targetPos[moveTarget];
		trailEffect->Init(&player->transform.pos);
		ChangeStatePlayer(PlayerState::Move);
	}
	//������Αҋ@��Ԃ֑J��
	else
	{
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