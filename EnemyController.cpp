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
	fsm[EnemyType::Stop] = new StopEnemyModel();
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
}

/**************************************
�X�V����
***************************************/
void EnemyController::Update()
{
	//�G�l�~�[��������
	//���͈�U�A������2�b������Stop�^�C�v�𐶐�
	cntFrame++;
	if (cntFrame % 120 == 0)
	{
		int start, end;
		start = RandomRange(0, 5);
		end = WrapAround(0, 5, start + RandomRange(1, 5));
		SetEnemy(EnemyType::Stop, LineTrailModel(start, end));
	}

	//���f���X�V����
	for (auto &model : modelContainer)
	{
		model->Update();
	}
}

/**************************************
�`�揈��
***************************************/
void EnemyController::Draw()
{
	for (auto &model : modelContainer)
	{
		model->Draw();
	}
}

/**************************************
�G�l�~�[��������
***************************************/
void EnemyController::SetEnemy(EnemyType type, LineTrailModel trailModel)
{
	//���g�p��EnemyModel������
	auto itr = find_if(modelContainer.begin(), modelContainer.end(), [](EnemyModel *model)
	{
		return !model->active;
	});

	//���������Ȃ�\�C�c���g�p
	if (itr != modelContainer.end())
	{
		(*itr)->Init(trailModel);
		(*itr)->ChangeState(fsm[type]);
	}
	//������Ȃ������̂ŐV�K�쐬
	else
	{
		EnemyModel *model = new EnemyModel();
		model->Init(trailModel);
		model->ChangeState(fsm[type]);
		modelContainer.push_back(model);
	}
	
}