//=====================================
//
//MidiumEnemyModel.cpp
//�@�\:���^�G�l�~�[���f��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "MidiumEnemyModel.h"

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
MidiumEnemyModel::MidiumEnemyModel() :
	step(0)
{
	cntFrame = 0;
	active = true;
	pos.z = PosZ;
}

/**************************************
����������
***************************************/
void MidiumEnemyModel::Init(std::vector<LineTrailModel>& moveList)
{
	moveTargetList.assign(moveList.begin(), moveList.end());

	D3DXVECTOR3 edgeR, edgeL;
	moveTargetList[step].GetEdgePos(&edgeR, &edgeL);

	enemyList.push_back(std::make_shared<EnemyMidium>());

	const D3DXVECTOR3 InitPos = D3DXVECTOR3(0.0f, -200.0f, 0.0f);
	D3DXVECTOR3 moveTarget = GetMoveTarget();
	enemyList[0]->VInit();
	dynamic_pointer_cast<EnemyMidium>(enemyList[0])->Set(InitPos);

	StartMove();
}

/**************************************
�X�V����
***************************************/
int MidiumEnemyModel::Update()
{
	int res = EnemyModelResult::StateContinuous;

	if (state == State::Wait)
		res = UpdateOnWait();
	else if (state == State::Moving)
		res = UpdateOnMoving();
	else if (state == State::Damage)
		res = UpdateOnWait();

	for (auto&& enemy : enemyList)
	{
		enemy->VUpdate();
	}

	return res;
}

/**************************************
�V���b�g���W�擾����
***************************************/
void MidiumEnemyModel::GetShotPos(std::vector<D3DXVECTOR3>& out)
{
	for (auto&& enemy : enemyList)
	{
		const int LoopMax = 5;
		for (int i = 0; i < LoopMax; i++)
		{
			out.push_back(enemy->m_Pos + ShotPosOffset);
		}
	}
}

/**************************************
�ړ��ڕW�擾����
***************************************/
D3DXVECTOR3 MidiumEnemyModel::GetMoveTarget()
{
	D3DXVECTOR3 edgeR, edgeL;
	moveTargetList[step].GetEdgePos(&edgeR, &edgeL);

	D3DXVECTOR3 moveTarget = edgeL + (edgeR - edgeL) / 2.0f;
	moveTarget.z = PosZ;

	return moveTarget;
}

/**************************************
Wait�X�V����
***************************************/
int MidiumEnemyModel::UpdateOnWait()
{
	const int WaitDuration = 180;
	const int AttackTiming = 120;

	cntFrame++;

	if (cntFrame == WaitDuration)
	{
		cntFrame = 0;
		StartMove();
	}

	if (cntFrame == AttackTiming)
	{
		return EnemyModelResult::AttackTiming;
	}

	return StateContinuous;
}

/**************************************
Moving�X�V����
***************************************/
int MidiumEnemyModel::UpdateOnMoving()
{
	cntFrame++;

	if (cntFrame == MoveDuration)
	{
		cntFrame = 0;
		state = State::Wait;

		//�ړ��悪�c���Ă��Ȃ���ΏI���A����ȊO��Wait�֑J�ڂ��ă`���[�W�J�n
		if (step <= moveTargetList.size())
		{
			collider->active = true;
			return ChargeTiming;
		}
		else
		{
			Uninit();
		}
	}

	return StateContinuous;
}

/**************************************
Damage�X�V����
***************************************/
int MidiumEnemyModel::UpdateOnDamage()
{
	cntFrame++;

	dynamic_pointer_cast<EnemyMidium>(enemyList[0])->HitAnimation();

	const int DamageDuration = 120;
	if (cntFrame == DamageDuration)
	{
		cntFrame = 0;
		StartMove();
	}

	return StateContinuous;
}

/**************************************
�ړ��J�n����
***************************************/
void MidiumEnemyModel::StartMove()
{
	cntFrame = 0;
	state = State::Moving;

	D3DXVECTOR3 moveTarget = step < moveTargetList.size() ? GetMoveTarget() : D3DXVECTOR3(0.0f, 200.0f, PosZ);
	dynamic_pointer_cast<EnemyMidium>(enemyList[0])->Move(moveTarget, MoveDuration);

	if (step < moveTargetList.size())
	{
		model = moveTargetList[step];
		collider->SetTrailIndex(model);
	}
	collider->active = false;

	step++;
}






