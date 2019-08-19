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
BossController::BossController()
{
	bossModel = new BossEnemyModel();
	bulletController = new EnemyBulletController();
}

/**************************************
�f�X�g���N�^
***************************************/
BossController::~BossController()
{
	SAFE_DELETE(bulletController);
	SAFE_DELETE(bossModel);
}

/**************************************
�X�V����
***************************************/
void BossController::Update()
{
	if (!active)
		return;

	bossModel->Update();

	bulletController->Update();
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