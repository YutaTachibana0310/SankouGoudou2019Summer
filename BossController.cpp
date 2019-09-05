//=====================================
//
//�{�X�R���g���[������[BossController.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "BossController.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
BossController::BossController(const Transform& player, BossUImanager& manager)
{
	bossModel = std::make_shared<BossEnemyModel>(player, manager);
	active = false;
}

/**************************************
�f�X�g���N�^
***************************************/
BossController::~BossController()
{
	bossModel.reset();
}

/**************************************
�X�V����
***************************************/
void BossController::Update()
{
	if (!active)
		return;

	bossModel->Update();

	if (bossModel->IsDesteoyed()) 
		SetActive(false);

}

/**************************************
�`�揈��
***************************************/
void BossController::Draw()
{
	if (!active)
		return;

	bossModel->Draw();
}

/**************************************
�A�N�e�B�u�Z�b�g����
***************************************/
void BossController::SetActive(bool state)
{
	active = state;
}

/**************************************
�A�N�e�B�u����
***************************************/
bool BossController::IsActive()
{
	return active;
}

/**************************************
�{�X�|�C���^�擾����
***************************************/
std::shared_ptr<BossEnemyModel> BossController::GetBoss()
{
	return bossModel;
}

/**************************************
�S�����X�g�擾����
***************************************/
void BossController::GetRebarList(std::list<std::shared_ptr<RebarObstacle>>& out)
{
	bossModel->GetRebarList(out);
}
