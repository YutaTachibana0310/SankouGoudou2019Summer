//=====================================
//
//TutorialEnemyModel.cpp
//�@�\:
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "TutorialEnemyModel.h"

/**************************************
�}�N����`
***************************************/
#define TUTORIALENEMY_INIT_OFFSET				(200.0f)	//�ڕW���W���珉�����W�ւ̋���
#define TUTORIALENEMY_DEST_FRAME				(60)		//�G�l�~�[�����C����ɓ��B����̂ɂ����鎞��

/**************************************
�R���X�g���N�^
***************************************/
TutorialEnemyModel::TutorialEnemyModel(LineTrailModel model, int enemyNum):
	EnemyModel()
{
	EnemyModel::Init(model);

	cntFrame = 0;
	collider->active = true;

	//Enemy�𐶐�
	for (int i = 0; i < enemyNum; i++)
	{
		enemyList.push_back(std::make_shared<EnemyTutorial>());
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
	D3DXVECTOR3 initOffset = cross * TUTORIALENEMY_INIT_OFFSET;

	//�G�l�~�[���Z�b�g
	for (auto& enemy : enemyList)
	{
		enemy->VInit();
		enemy->VSet(edgeR + initOffset, edgeR, TUTORIALENEMY_DEST_FRAME);
		edgeR += enemyLength;
	}
}

/**************************************
�X�V����
***************************************/
int TutorialEnemyModel::Update()
{
	for (auto&& enemy : enemyList)
	{
		enemy->VUpdate();
	}

	return StateContinuous;

}
