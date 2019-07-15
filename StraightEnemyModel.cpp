//=====================================
//
//�X�g���[�g�G�l�~�[���f������[StraightEnemyModel.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "StraightEnemyModel.h"
#include "enemy.h"
#include "Framework\Easing.h"
#include "GameParticleManager.h"

/**************************************
�}�N����`
***************************************/
typedef EnemyModel Base;

#define STRAIGHTENEMY_REACH_FRAME		(180)

/**************************************
�R���X�g���N�^
***************************************/
StraightEnemyModel::StraightEnemyModel() : StartPosZ(400.0f), DestPosZ(-200.0f)
{

}

/**************************************
�f�X�g���N�^
***************************************/
StraightEnemyModel::~StraightEnemyModel()
{

}

/**************************************
����������
***************************************/
void StraightEnemyModel::Init(LineTrailModel model)
{
	Base::Init(model);

	cntFrame = 0;
	collider->active = true;

	//�G�l�~�[����
	for (int i = 0; i < 5; i++)
	{
		enemyList.push_back(new EnemyStraight());
	}

	//Enemy�̏�����
	D3DXVECTOR3 edgeR, edgeL;
	model.GetEdgePos(&edgeR, &edgeL);
	edgeL.z = edgeR.z = StartPosZ;
	
	D3DXVECTOR3 offset = (edgeL - edgeR) / ((float)enemyList.size() - 1);
	
	D3DXVECTOR3 dest = edgeR;
	dest.z = DestPosZ;

	for (auto& enemy : enemyList)
	{
		enemy->VInit();
		enemy->VSet(edgeR, dest, STRAIGHTENEMY_REACH_FRAME);
		edgeR += offset;
		dest += offset;
	}

	//���[�v�G�t�F�N�g�Z�b�g
	for (auto& enemy : enemyList)
	{
		D3DXVECTOR3 setPos = enemy->m_Pos + D3DXVECTOR3(0.0f, 0.0f, -50.0f);
		GameParticleManager::Instance()->SetEnemyWarpHole(&setPos);
	}

}

/**************************************
�X�V����
***************************************/
int StraightEnemyModel::Update()
{
	cntFrame++;
	float t = (float)cntFrame / (float)STRAIGHTENEMY_REACH_FRAME;

	pos.z = Easing<float>::GetEasingValue(t, &StartPosZ, &DestPosZ, EasingType::InCubic);

	if (cntFrame == STRAIGHTENEMY_REACH_FRAME)
	{
		Uninit();
	}

	for (auto& enemy : enemyList)
	{
		enemy->VUpdate();
	}

	return StateContinuous;
}