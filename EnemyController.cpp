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
	for (auto &model : modelList)
	{
		SAFE_DELETE(model);
	}
	modelList.clear();
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
	for (auto &model : modelList)
	{
		model->Uninit();
	}
}

/**************************************
�X�V����
***************************************/
void EnemyController::Update()
{
	//���f���X�V����
	for (auto &model : modelList)
	{
		model->Update();
	}

	//�I���������f�����폜����
	for (auto& model : modelList)
	{
		if (!model->active)
			SAFE_DELETE(model);
	}

	//�폜�������f�������X�g����폜
	modelList.remove_if([](EnemyModel* model)
	{
		return model == nullptr;
	});
}

/**************************************
�`�揈��
***************************************/
void EnemyController::Draw()
{
	//�G�l�~�[���f���`��
	for (auto &model : modelList)
	{
		model->Draw();
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

	modelList.push_back(model);
}