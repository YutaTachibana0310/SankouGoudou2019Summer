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
	int stateResult = player->Update();

	if (stateResult != STATE_CONTINUOUS)
		OnPlayerStateFinish();

	bulletController->Update();

	trailEffect->Update();

	bomberController->Update();
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
	for (int i = 0; i < INPUTBUTTON_MAX; i++)
	{
		if (!IsEntered(i))
			continue;

		PushInput(i);
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

	//�v���C���[�̓��͊Ԋu�����Z�b�g
	player->inputInterval = 0;

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
		LineTrailModel modelTrail;
		model->GetPlayerTrail(&modelTrail);
		bulletController->SetPlayerBullet(modelTrail);
	}

	//��M��������
	if (model->CheckOneStroke())
	{

		//�{������
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