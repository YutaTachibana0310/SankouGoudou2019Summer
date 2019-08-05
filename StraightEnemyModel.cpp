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
#define STRAIGHTENEMY_ACTIVATE_FRAME	(30)
//0805 BA
#define SHADOW_FALSE_FRAME				(1000)

/**************************************
�R���X�g���N�^
***************************************/
StraightEnemyModel::StraightEnemyModel() : StartPosZ(300.0f), DestPosZ(-200.0f)
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
	collider->active = false;

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
		enemy->m_Active = false;
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

	//�G�l�~�[�̃A�N�e�B�x�C�g
	if (cntFrame == STRAIGHTENEMY_ACTIVATE_FRAME)
	{
		for (auto& enemy : enemyList)
		{
			enemy->m_Active = true;
		}
		collider->active = true;
	}

	//�����蔻��̈ړ�����
	if (cntFrame >= STRAIGHTENEMY_ACTIVATE_FRAME)
	{
		float t = (float)(cntFrame - STRAIGHTENEMY_ACTIVATE_FRAME) / (float)STRAIGHTENEMY_REACH_FRAME;
		pos.z = Easing<float>::GetEasingValue(t, &StartPosZ, &DestPosZ, EasingType::InCubic);
	}

	//�I������
	if (cntFrame == STRAIGHTENEMY_REACH_FRAME + STRAIGHTENEMY_ACTIVATE_FRAME+ SHADOW_FALSE_FRAME)
	{
		Uninit();
	}

	//��������G�l�~�[���X�V
	for (auto& enemy : enemyList)
	{
		enemy->VUpdate();
	}

	return StateContinuous;
}