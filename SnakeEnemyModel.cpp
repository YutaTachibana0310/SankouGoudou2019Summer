//=====================================
//
//�X�l�[�N�G�l�~�[���f������[SnakeEnemyModel.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "SnakeEnemyModel.h"
#include "enemy.h"
#include "GameParticleManager.h"
#include "ScoreManager.h"

using namespace std;

/**************************************
�}�N����`
***************************************/
typedef EnemyModel Base;

#define SNAKEENEMY_START_OFFSET			(400.0f)		//�G�l�~�[�̏������W�̃I�t�Z�b�g
#define SNAKEENEMY_INIT_DURATION		(45)			//�ŏ��̃^�[�Q�b�g�֌������̂ɂ����鎞��-
#define SNAKEENEMY_MOVE_DURATION		(90)			//�G�l�~�[���ړ��ɂ����鎞��
#define SNAKEENMY_GENERATE_NUM			(7)				//��������G�l�~�[�̐�
#define SNAKEENEMY_GENERATE_INTERVAL	(10)			//�����C���^�[�o��
#define SNAKEENEMY_GENERATE_DURATION	(SNAKEENMY_GENERATE_NUM*SNAKEENEMY_GENERATE_INTERVAL)

/**************************************
����������
***************************************/
void SnakeEnemyModel::Init(vector<int> destList)
{
	active = true;
	cntFrame = 0;
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
		colliderList[i]->active = false;
	}

	//�ړ����W���X�g���쐬
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

	//�ړ����ԃ��X�g�쐬
	timeList.resize(moveTargetList.size());
	for (UINT i = 0; i < moveTargetList.size(); i++)
	{
		int t = i == 0 || i == moveTargetList.size() - 1 ? SNAKEENEMY_INIT_DURATION : SNAKEENEMY_MOVE_DURATION;
		timeList[i] = t;
	}

	//�ŏ��̃G�l�~�[�𐶐�
	EnemySnake *enemy = new EnemySnake();
	enemy->VInit();
	enemy->Set(moveTargetList, timeList, 60);
	enemyList.push_back(enemy);
}

/**************************************
�X�V����
***************************************/
int SnakeEnemyModel::Update()
{
	//�G�l�~�[�̐���
	if (++cntFrame < SNAKEENEMY_GENERATE_DURATION)
	{
		//�C���^�[�o�������ɍ쐬
		if (cntFrame % SNAKEENEMY_GENERATE_INTERVAL == 0)
		{
			EnemySnake *enemy = new EnemySnake();
			enemy->VInit();
			enemy->Set(moveTargetList, timeList, 60);
			enemyList.push_back(enemy);
		}
	}

	//�G�l�~�[�̍X�V
	for (auto& enemy : enemyList)
	{
		enemy->VUpdate();
	}

	//�����蔻��̍X�V
	for (auto& enemy : enemyList)
	{
		EnemySnake* snake = static_cast<EnemySnake*>(enemy);

		UINT next = snake->m_CurrentIndex - 1;
		UINT current = snake->m_PrevIndex - 1;

		TrailCollider *nextCollider = next < colliderList.size() ? colliderList[next] : NULL;
		TrailCollider *currentCollider = current < colliderList.size() ? colliderList[current] : NULL;
		SwapInColliderMap(currentCollider, nextCollider, snake);
	}

	//�I������
	if (cntFrame > SNAKEENEMY_GENERATE_DURATION)
	{
		//�A�N�e�B�u�ȃG�l�~�[���c���Ă��邩�m�F
		bool isActive = false;
		for (auto& enemy : enemyList)
		{
			isActive |= enemy->m_Active;
		}

		//�c���Ă��Ȃ���ΏI��
		if (!isActive)
			Uninit();
	}

	return 0;
}

/**************************************
�`�揈��
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
void SnakeEnemyModel::OnNotified(ObserveSubject *notifier)
{
	TrailCollider *entity = static_cast<TrailCollider*>(notifier);

	//�����蔻��ɑ�����G�l�~�[���ׂĂɃ_���[�W����
	for (auto& enemy : colliderMap[entity])
	{
		enemy->m_FlgDestroyed = true;
	}

	//�����G�l�~�[���X�g���N���A
	colliderMap[entity].clear();

	//�Փ˂��������蔻����A�N�e�B�u��
	entity->active = false;
}

/**************************************
�����蔻�������ւ�����
***************************************/
void SnakeEnemyModel::SwapInColliderMap(TrailCollider* current, TrailCollider* next, EnemySnake* enemy)
{
	//��������֓���ւ��悤�Ƃ��Ă����瑁�����^�[��
	if (current == next)
		return;

	//����ւ�����NULL�łȂ����
	if (current != NULL)
	{
		//��������̃G�l�~�[���X�g�̒�����Y������G�l�~�[������
		auto itr = find(colliderMap[current].begin(), colliderMap[current].end(), enemy);

		//���X�g���痣�E
		colliderMap[current].erase(itr);

		//��������G�l�~�[�����Ȃ��Ȃ��Ă����画����A�N�e�B�u��
		if (colliderMap[current].size() == 0)
			current->active = false;
	}

	//����ւ��悪NULL�ł����return
	if (next == NULL)
		return;

	//����ւ���̃G�l�~�[���X�g�փv�b�V��
	colliderMap[next].push_back(enemy);

	next->active = true;
}