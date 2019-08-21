//=====================================
//
//�{�X�G�l�~�[�A�N�^�[����[BossEnemyActor.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "BossEnemyActor.h"
#include "Framework\AnimationManager.h"
#include "Framework\Easing.h"
#include "Framework\Vector3.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
BossEnemyActor::BossEnemyActor()
{
	animManager = new AnimationManager();

	//���f���t�@�C���ǂݍ���
	const char* ModelFileName = "data/MODEL/Boss.x";
	animManager->LoadXFile(ModelFileName, "Boss");

	//�A�j���[�V�����ǂݍ���
	const char* AnimationSetName[] = {
		"Flying", "Attack01", "Attack02", "Damage", "Death", "Idle", "LargeDamage"
	};
	for (UINT i = 0; i < AnimID::Max; i++)
	{
		animManager->LoadAnimation(AnimationSetName[i], i, 0.3f);
	}

	//�A�j���[�V�����X�s�[�h�ݒ�
	const float AnimationPlaySpeed[] = {
		1.0f, 0.6f, 0.6f, 1.5f, 1.0f, 1.0f, 1.5f
	};
	for (UINT i = 0; i < AnimID::Max; i++)
	{
		animManager->SetPlaySpeed(i, AnimationPlaySpeed[i]);
	}

	//�J�ڊ֌W�ݒ�
	animManager->SetFinishTransition(AnimID::Attack01, AnimID::Idle);
	animManager->SetFinishTransition(AnimID::Attack02, AnimID::Idle);
	animManager->SetFinishTransition(AnimID::Damage, AnimID::Idle);
	animManager->SetFinishTransition(AnimID::LargeDamage, AnimID::Idle);

	//�t���O������
	inMoving = false;
	inRotaiton = false;

	transform.scale = 50.0f * D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

/**************************************
�f�X�g���N�^
***************************************/
BossEnemyActor::~BossEnemyActor()
{
	SAFE_DELETE(animManager);
}

/**************************************
�X�V����
***************************************/
void BossEnemyActor::Update()
{
	_Move();
	
	_Rotate();

	animManager->Update();
}

/**************************************
�`�揈��
***************************************/
void BossEnemyActor::Draw()
{
	transform.SetWorld();

	D3DXMATRIX world = transform.GetMatrix();
	animManager->Draw(&world);
}

/**************************************
�ړ�����
***************************************/
void BossEnemyActor::Move(const D3DXVECTOR3& target, int duration)
{
	if (inMoving)
		return;

	targetPos = target;
	prevPos = transform.pos;
	cntMove = 0;
	durationMove = duration;
	inMoving = true;
}

/**************************************
��]����
***************************************/
void BossEnemyActor::Rotate(const D3DXVECTOR3& target, float magnitude)
{
	if (inRotaiton)
		return;

	targetForward = target;
	magnitudeRotate = magnitude;
	inRotaiton = true;
}

/**************************************
�A�j���[�V�����ύX����
***************************************/
void BossEnemyActor::ChangeAnimation(AnimID next)
{
	animManager->ChangeAnim(next, true);
}

/**************************************
�ړ������i�����j
***************************************/
void BossEnemyActor::_Move()
{
	if (!inMoving)
		return;

	cntMove++;

	float t = (float)cntMove / durationMove;
	transform.pos = Easing::EaseValue(t, prevPos, targetPos, EaseType::OutBack);

	if (cntMove == durationMove)
		inMoving = false;
}

/**************************************
��]�����i�����j
***************************************/
void BossEnemyActor::_Rotate()
{
	if (!inRotaiton)
		return;

	float angle = Vector3::Angle(transform.Forward(), targetForward);
	D3DXVECTOR3 axis = Vector3::Axis(transform.Forward(), targetForward);
	transform.RotateByAxis(angle * magnitudeRotate, axis);

	if (angle < 0.01f)
		inRotaiton = false;
}