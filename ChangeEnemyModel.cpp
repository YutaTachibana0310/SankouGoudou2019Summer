//=====================================
//
//�X�g�b�v�G�l�~�[���f������[StopEnemyModel.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "ChangeEnemyModel.h"
#include "enemy.h"

/**************************************
�}�N����`
***************************************/
//����������Ă��瓖���蔻�肪�A�N�e�B�u�ɂȂ�^�C�~���O
#define STOPENEMY_TIME_COLLIDER_ACTIVATE	(60)

//�����蔻�肪�����ɂȂ�^�C�~���O
#define STOPENEMT_TIME_ESCAPE				(300 + STOPENEMY_TIME_COLLIDER_ACTIVATE)

//�I���^�C�~���O
#define STOPENEMY_TIME_UNINIT				(60 + STOPENEMT_TIME_ESCAPE)

typedef EnemyModel Base;

/**************************************
�\���̒�`
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
ChangeEnemyModel::ChangeEnemyModel()
{

}

/**************************************
�f�X�g���N�^
***************************************/
ChangeEnemyModel::~ChangeEnemyModel()
{

}

/**************************************
����������
***************************************/
void ChangeEnemyModel::Init(LineTrailModel model)
{
	Base::Init(model);

	cntFrame = 0;
	collider->active = false;

	//�Ƃ肠����Enemy��5�̐���
	for (int i = 0; i < 5; i++)
	{
		enemyList.push_back(new EnemyChange());
	}

	//EnemyModel�ɑ�����Enemy�Ɉړ��w�����o��
	//TODO:�����ʒu��ύX�ł���悤�ɂ���
	D3DXVECTOR3 InitPos = D3DXVECTOR3(0.0f, 500.0f, 250.0f);
	D3DXVECTOR3 edgeL, edgeR;
	model.GetEdgePos(&edgeR, &edgeL);
	edgeL.z = edgeR.z = 250.0f;
	D3DXVECTOR3 offset = (edgeL - edgeR) / ((float)enemyList.size() - 1);

	for (auto& enemy : enemyList)
	{
		enemy->Init();
		enemy->SetVec(InitPos, edgeR, STOPENEMY_TIME_COLLIDER_ACTIVATE, 300, D3DXVECTOR3(0.0f, 15.0f, 0.0));
		edgeR += offset;
	}
}

/**************************************
�X�V����
***************************************/
int ChangeEnemyModel::Update()
{
	cntFrame++;

	//60�t���[���ڂœ����蔻����A�N�e�B�u�ɂ���
	if (cntFrame == STOPENEMY_TIME_COLLIDER_ACTIVATE)
		collider->active = true;

	//�A�N�e�B�u�ɂȂ��Ă���300�t���[���ŗ��E����
	if (cntFrame == STOPENEMT_TIME_ESCAPE)
		collider->active = false;

	//���E�J�n���Ă���60�t���[���ŏI������
	if (cntFrame == STOPENEMY_TIME_UNINIT)
		Uninit();

	for (auto& enemy : enemyList)
	{
		enemy->Update();
	}

	return StateContinuous;
}