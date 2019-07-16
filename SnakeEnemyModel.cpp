//=====================================
//
//�X�l�[�N�G�l�~�[���f������[SnakeEnemyModel.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "SnakeEnemyModel.h"
#include "enemy.h"

using namespace std;

/**************************************
�}�N����`
***************************************/
typedef EnemyModel Base;

#define SNAKEENEMY_START_OFFSET		(400.0f)
#define SNAKEENEMY_MOVE_DURATION	(30.0f)

/**************************************
����������
***************************************/
void SnakeEnemyModel::Init(vector<int> destList)
{

	collider->active = false;
	pos.z = 250.0f;

	//destList���烂�f�����X�g���쐬
	vector<LineTrailModel> modelList;
	for (UINT i = 0; i < destList.size() - 1; i++)
	{
		modelList.push_back(LineTrailModel(destList[i], destList[i + 1]));
	}

	//���f�����X�g����R���C�_�[���X�g���쐬
	colliderList.resize(modelList.size());
	for (UINT i = 0; i < modelList.size(); i++)
	{
		colliderList[i] = new TrailCollider(TrailColliderTag::Enemy);
		colliderList[i]->SetTrailIndex(modelList[i]);
		colliderList[i]->SetAddressZ(&pos.z);
		colliderList[i]->AddObserver(this);
	}

	//�ړ����W���X�g���쐬
	vector<D3DXVECTOR3> moveTargetList;
	moveTargetList.resize(destList.size() + 2);

	//destList������W���擾���Đݒ�
	for (UINT i = 0; i < destList.size(); i++)
	{
		moveTargetList[i + 1] = LineTrailModel::GetEdgePos(destList[i]);
	}

	//�������W���v�Z
	D3DXVECTOR3 initDiff = moveTargetList[1] - moveTargetList[2];
	D3DXVec3Normalize(&initDiff, &initDiff);
	moveTargetList[0] = moveTargetList[1] + initDiff * SNAKEENEMY_START_OFFSET;

	//�ŏI���W���v�Z
	UINT lastIndex = moveTargetList.size() - 1;
	D3DXVECTOR3 lastDiff = moveTargetList[lastIndex - 1] - moveTargetList[lastIndex - 2];
	D3DXVec3Normalize(&lastDiff, &lastDiff);
	moveTargetList[lastIndex] = moveTargetList[lastIndex - 1] + lastDiff * SNAKEENEMY_START_OFFSET;

	//Z���W��ݒ�
	for (auto& target : moveTargetList)
	{
		target.z = pos.z;
	}

	//�ړ����ԃ��X�g
	vector<float> timeList;
	timeList.resize(moveTargetList.size());
	for (auto& time : timeList)
	{
		time = SNAKEENEMY_MOVE_DURATION;
	}

	//�G�l�~�[���쐬
	EnemySnake *snake = new EnemySnake;
	snake->VInit();
	snake->Set(moveTargetList, timeList, 60.0f);
	enemyList.push_back(snake);
}

/**************************************
�X�V����
***************************************/
int SnakeEnemyModel::Update()
{
	for (auto& enemy : enemyList)
	{
		enemy->VUpdate();
	}

	return 0;
}

/**************************************
�X�V����
***************************************/
void SnakeEnemyModel::Draw()
{
	for (auto& enemy : enemyList)
	{
		enemy->VDraw();
	}

	for (auto& collider : colliderList)
	{
		TrailCollider::DrawCollider(collider);
	}
}

/**************************************
�Փ˔���
***************************************/