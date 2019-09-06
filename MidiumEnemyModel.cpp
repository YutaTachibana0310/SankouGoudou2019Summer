//=====================================
//
//MidiumEnemyModel.cpp
//�@�\:���^�G�l�~�[���f��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "MidiumEnemyModel.h"
#include "GameParticleManager.h"

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
MidiumEnemyModel::MidiumEnemyModel() :
	step(0),
	hp(3)
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

	for (int i = 0; i < EnemyNum; i++)
	{
		enemyList.push_back(std::make_shared<EnemyMidium>());
		const D3DXVECTOR3 InitPos = D3DXVECTOR3(0.0f, -200.0f, PosZ);
		D3DXVECTOR3 moveTarget = GetMoveTarget(i);
		enemyList[i]->VInit();
		dynamic_pointer_cast<EnemyMidium>(enemyList[i])->Set(InitPos);

	}


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
		res = UpdateOnDamage();

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
�Փ˔���ʒm����
***************************************/
void MidiumEnemyModel::OnNotified(ObserveSubject * notifier)
{
	//�_���[�W���o���͔��肵�Ȃ�
	if (state == State::Damage)
		return;

	hp--;

	if (hp == 0)
	{
		for (auto&& enemy : enemyList)
		{
			enemy->m_FlgDestroyed = true;
		}

	}

	for (auto&& emitter : chageEffectList)
	{
		if (emitter != NULL)
			emitter->active = false;
	}

	for (auto&& enemy : enemyList)
	{
		GameParticleManager::Instance()->SetEnemyExplosion(&enemy->m_Pos);
	}

	cntFrame = 0;
	state = State::Damage;
}

/**************************************
�ړ��ڕW�擾����
***************************************/
D3DXVECTOR3 MidiumEnemyModel::GetMoveTarget(int i)
{
	D3DXVECTOR3 edgeR, edgeL;
	moveTargetList[step].GetEdgePos(&edgeR, &edgeL);
	edgeR.z = edgeL.z = PosZ;

	D3DXVECTOR3 offset = (edgeR - edgeL) / (float)(EnemyNum + 1);

	return edgeL + offset * (i + 1);
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

	for (auto&& enemy : enemyList)
	{
		dynamic_pointer_cast<EnemyMidium>(enemy)->HitAnimation();
	}

	const int DamageDuration = 59;
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

	int cntLoop = 0;
	for (auto&& enemy : enemyList)
	{
		D3DXVECTOR3 moveTarget = step < moveTargetList.size() ? GetMoveTarget(cntLoop) : D3DXVECTOR3(0.0f, 200.0f, PosZ);
		dynamic_pointer_cast<EnemyMidium>(enemy)->Move(moveTarget, MoveDuration);
		cntLoop++;
	}

	if (step < moveTargetList.size())
	{
		model = moveTargetList[step];
		collider->SetTrailIndex(model);
	}
	collider->active = false;

	step++;
}






