//=====================================
//
//�G�l�~�[�R���g���[���[����[EnemyController.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "EnemyController.h"
#include "TestEnemyModel.h"

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
	fsm[EnemyType::Test] = new TestEnemyModel();
}

/**************************************
�f�X�g���N�^
***************************************/
EnemyController::~EnemyController()
{
	for (auto &model : modelContainer)
	{
		SAFE_DELETE(model);
	}
}

/**************************************
����������
***************************************/
void EnemyController::Init()
{
	modelContainer.push_back(new EnemyModel());
	modelContainer[0]->ChangeState(fsm[EnemyType::Test]);
	modelContainer[0]->Init(LineTrailModel(0, 1));
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