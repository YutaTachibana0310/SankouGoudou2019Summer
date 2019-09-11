//=====================================
//
//TutorialEnemyController.cpp
//�@�\:�`���[�g���A���G�l�~�[�R���g���[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "TutorialEnemyController.h"
#include "Framework\ResourceManager.h"
#include "TutorialEnemyModel.h"
#include "LineTrailModel.h"

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
TutorialEnemyController::TutorialEnemyController()
{
	ResourceManager::Instance()->LoadMesh("Enemy", "data/MODEL/Enemy/drone.x");
}

/**************************************
�f�X�g���N�^
***************************************/
TutorialEnemyController::~TutorialEnemyController()
{
	for (auto&& model : modelList)
	{
		SAFE_DELETE(model);
	}
	modelList.clear();
}

/**************************************
�X�V����
***************************************/
void TutorialEnemyController::Update()
{
	//���X�g���󂾂�����G�l�~�[�ǉ�
	if (modelList.empty())
	{
		int start = RandomRange(0, 5);
		int end = WrapAround(0, 5, start + RandomRange(1, 5));
		LineTrailModel model = LineTrailModel(start, end);
		modelList.push_back(new TutorialEnemyModel(model, 3));
	}

	for (auto&& model : modelList)
	{
		model->Update();
	}

	for (auto&& model : modelList)
	{
		model->CheckDestroied();
		if (!model->active)
			SAFE_DELETE(model);
	}

	modelList.remove_if([](EnemyModel* model)
	{
		return model == nullptr;
	});
}

/**************************************
�`�揈��
***************************************/
void TutorialEnemyController::Draw()
{
	for (auto&& model : modelList)
	{
		model->Draw();
	}
}

/**************************************
�G�l�~�[���݊m�F
***************************************/
bool TutorialEnemyController::IsExistEnemy()
{
	return !modelList.empty();
}

/**************************************
�G�l�~�[�擾����
***************************************/
void TutorialEnemyController::GetEnemyList(std::list<std::shared_ptr<Enemy>>& out)
{
	for (auto&& model : modelList)
	{
		model->GetEnemy(out);
	}
}
