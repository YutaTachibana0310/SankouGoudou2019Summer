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
#define CHANGEENEMY_TIME_COLLIDER_ACTIVATE	(30)
#define CHANGEENEMY_DEST_FRAME				(60)		//�G�l�~�[�����C����ɓ��B����̂ɂ����鎞��

//�U���^�C�~���O
#define CHANGEENEMY_TIME_ATTACK				(120 + CHANGEENEMY_DEST_FRAME)

//�����蔻�肪�����ɂȂ�^�C�~���O
#define CHANGEENEMY_TIME_ESCAPE				(300 + CHANGEENEMY_DEST_FRAME)

//�I���^�C�~���O
#define CHANGEENEMY_TIME_UNINIT				(60 + CHANGEENEMY_TIME_ESCAPE)

#define CHANGEENEMY_GENERATE_NUM			(3)			//�G�l�~�[�̐�����	
#define CHANGEENEMY_INIT_OFFSET				(200.0f)	//�ڕW���W���珉�����W�ւ̋���


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
void ChangeEnemyModel::Init(LineTrailModel model, int enemyNum)
{
	Base::Init(model);

	cntFrame = 0;
	collider->active = false;

	//Enemy�𐶐�
	for (int i = 0; i < enemyNum; i++)
	{
		enemyList.push_back(std::make_shared<EnemyChange>());
	}

	//���C���̒[�_�����߂�
	D3DXVECTOR3 edgeL, edgeR;
	model.GetEdgePos(&edgeR, &edgeL);
	edgeL.z = edgeR.z = 250.0f;

	//�G�l�~�[���m�̋��������߂�
	D3DXVECTOR3 enemyLength = (edgeL - edgeR) / ((float)enemyList.size() + 1);
	edgeR += enemyLength;

	//���C���ɑ΂��Đ����ȃx�N�g�������߂�
	D3DXVECTOR3 cross;
	D3DXVec3Cross(&cross, &(edgeL - edgeR), &D3DXVECTOR3(0.0f, 0.0f, 1.0f));
	D3DXVec3Normalize(&cross, &cross);

	//�������W���v�Z
	D3DXVECTOR3 initOffset = cross * CHANGEENEMY_INIT_OFFSET;

	//�G�l�~�[���Z�b�g
	for (auto& enemy : enemyList)
	{
		enemy->VInit();
		enemy->VSetVec(edgeR + initOffset, edgeR, CHANGEENEMY_DEST_FRAME, CHANGEENEMY_TIME_ESCAPE - CHANGEENEMY_TIME_COLLIDER_ACTIVATE, D3DXVECTOR3(0.0f, 15.0f, 0.0));
		edgeR += enemyLength;
	}
}

/**************************************
�X�V����
***************************************/
int ChangeEnemyModel::Update()
{
	cntFrame++;

	//60�t���[���ڂœ����蔻����A�N�e�B�u�ɂ���
	if (cntFrame == CHANGEENEMY_TIME_COLLIDER_ACTIVATE)
		collider->active = true;
	
	//�A�N�e�B�u�ɂȂ��Ă���300�t���[���ŗ��E����
	if (cntFrame == CHANGEENEMY_TIME_ESCAPE)
		collider->active = false;

	//���E�J�n���Ă���60�t���[���ŏI������
	if (cntFrame == CHANGEENEMY_TIME_UNINIT)
		Uninit();

	for (auto& enemy : enemyList)
	{
		enemy->VUpdate();
	}

	//�A�N�e�B�u�ɂȂ��Ă���120�t���[���ōU��
	if (cntFrame == CHANGEENEMY_TIME_ATTACK)
		return AttackTiming;
	//�G�l�~�[�̓����Ɠ����Ƀ`���[�W���o
	else if (cntFrame == CHANGEENEMY_DEST_FRAME)
		return ChargeTiming;
	else
		return StateContinuous;
}