//=====================================
//
//�G�l�~�[�R���g���[���[����[EnemyController.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "EnemyController.h"
#include "TestEnemyModel.h"
#include "StopEnemyModel.h"

#include <algorithm>

using namespace std;

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
EnemyController::EnemyController()
{
	//�X�e�[�g�}�V���쐬
	fsm[EnemyModelType::Stop] = new StopEnemyModel();
}

/**************************************
�f�X�g���N�^
***************************************/
EnemyController::~EnemyController()
{
	//���f���R���e�i�N���A
	for (auto &model : modelContainer)
	{
		SAFE_DELETE(model);
	}
	modelContainer.clear();

	//�X�e�[�g�}�V���N���A
	for (auto &state : fsm)
	{
		SAFE_DELETE(state.second);
	}
	fsm.clear();

	//�G�l�~�[�R���e�i�N���A
	for (auto& enemyList : enemyContainer)
	{
		for (auto& enemy : enemyList.second)
		{
			SAFE_DELETE(enemy);
		}
		enemyList.second.clear();
	}
	enemyContainer.clear();
}

/**************************************
����������
***************************************/
void EnemyController::Init()
{
	cntFrame = 0;
}

/**************************************
�I������
***************************************/
void EnemyController::Uninit()
{
	for (auto &model : modelContainer)
	{
		model->Uninit();
	}

	for (auto& enemyList : enemyContainer)
	{
		for (auto& enemy : enemyList.second)
		{
			enemy->VUninit();
		}
	}
}

/**************************************
�X�V����
***************************************/
void EnemyController::Update()
{
	//���f���X�V����
	for (auto &model : modelContainer)
	{
		model->Update();
	}

	//�G�l�~�[�X�V����
	for (auto &enemyList : enemyContainer)
	{
		for (auto& enemy : enemyList.second)
		{
			enemy->VUpdate();
		}
	}
}

/**************************************
�`�揈��
***************************************/
void EnemyController::Draw()
{
	//�G�l�~�[���f���`��
	for (auto &model : modelContainer)
	{
		model->Draw();
	}

	//�G�l�~�[�`��
	for (auto& enemyList : enemyContainer)
	{
		for (auto& enemy : enemyList.second)
		{
			enemy->VDraw();
		}
	}
}

/**************************************
�G�l�~�[�����C���^�[�t�F�[�X
***************************************/
void EnemyController::SetEnemy()
{
	//���͈�U�A������2�b������Stop�^�C�v�𐶐�
	cntFrame++;
	if (cntFrame % 120 == 0)
	{
		int start, end;
		start = RandomRange(0, 5);
		end = WrapAround(0, 5, start + RandomRange(1, 5));
		_SetEnemy(EnemyModelType::Stop, LineTrailModel(start, end));
	}
}

/**************************************
�G�l�~�[���������i���f���Łj
***************************************/
void EnemyController::_SetEnemy(EnemyModelType type, LineTrailModel trailModel)
{
	//���g�p��EnemyModel������
	auto itr = find_if(modelContainer.begin(), modelContainer.end(), [](EnemyModel *model)
	{
		return !model->active;
	});

	//���������Ȃ�\�C�c���g�p
	EnemyModel *model = NULL;
	if (itr != modelContainer.end())
	{
		model = (*itr);
	}
	//������Ȃ������̂ŐV�K�쐬
	else
	{
		model = new EnemyModel();
		modelContainer.push_back(model);
	}

	//�G�l�~�[�̎��̂𐶐�
	switch (type)
	{
	case EnemyModelType::Stop:
		_SetEnemyChange(model);
		break;
	}
	
	//������
	model->Init(trailModel);
	model->ChangeState(fsm[type]);
}

/**************************************
�G�l�~�[��������(���̔�)
***************************************/
void EnemyController::_SetEnemyChange(EnemyModel* model)
{
	//TODO:�Z�b�g���؂�ւ�����悤�ɂ���
	UINT setNum = 5;
	UINT setCount = 0;
	const EnemyType Type = EnemyType::Change;

	//�R���e�i�̒��Ŗ��g�p�̃G�l�~�[���g�p
	for (UINT i = 0; i < setNum; i++)
	{
		//���g�p�̃G�l�~�[������
		auto itr = find_if(enemyContainer[Type].begin(), enemyContainer[Type].end(), [](Enemy* enemy)
		{
			return !enemy->m_Active;
		});

		//���Ȃ������̂�break
		if (itr == enemyContainer[Type].end())
			break;

		//EnemyModel�ɒǉ�
		model->AddEnemy((*itr));
		(*itr)->m_Active = true;
		setCount++;
	}

	//����Ȃ���������V�K�쐬
	for (UINT i = setCount; i < setNum; i++)
	{
		Enemy* newEnemy = new EnemyChange();

		//Enemy���f���ɒǉ����ăR���e�i�o�^
		model->AddEnemy(newEnemy);
		enemyContainer[Type].push_back(newEnemy);
	}
}