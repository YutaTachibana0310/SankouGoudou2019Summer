//=====================================
//
//�G�l�~�[�R���g���[���[����[EnemyController.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "EnemyController.h"
#include "TestEnemyModel.h"
#include "ChangeEnemyModel.h"

#include <algorithm>
#include "Framework\ResourceManager.h"

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
	//���\�[�X�ǂݍ���
	//����̓V�[���I������Game.cpp�ňꊇ���ĊJ������
	ResourceManager::Instance()->LoadMesh("Enemy", "data/MODEL/airplane000.x");
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
			enemy->Uninit();
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
			enemy->Update();
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
	//for (auto& enemyList : enemyContainer)
	//{
	//	for (auto& enemy : enemyList.second)
	//	{
	//		enemy->Draw();
	//	}
	//}
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
		_SetEnemy(string("Change"), LineTrailModel(start, end));
	}
}

/**************************************
�G�l�~�[���������i���f���Łj
***************************************/
void EnemyController::_SetEnemy(string type, LineTrailModel trailModel)
{
	EnemyModel *model = nullptr;
	if (type == "Change")
		model = new ChangeEnemyModel();

	if (model == nullptr)
		return;

	//������
	model->Init(trailModel);

	modelContainer.push_back(model);
}

/**************************************
�G�l�~�[��������(���̔�)
***************************************/
void EnemyController::_SetEnemyChange(EnemyModel* model)
{

}