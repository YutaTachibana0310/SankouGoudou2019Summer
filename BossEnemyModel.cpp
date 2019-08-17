//=====================================
//
//�{�X�G�l�~�[���f������[BossEnemyModel.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "BossEnemyModel.h"
#include "BossEnemyActor.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
BossEnemyModel::BossEnemyModel()
{
	actor = new BossEnemyActor();

	actor->transform.pos = D3DXVECTOR3(0.0f, -200.0f, -2000.0f);
	actor->transform.Rotate(0.0f, 180.0f, 0.0f);
	actor->Move(D3DXVECTOR3(0.0f, -200.0f, 1500.0f), 300);

	actor->ChangeAnimation(BossEnemyActor::AnimID::Flying);
}

/**************************************
�f�X�g���N�^
***************************************/
BossEnemyModel::~BossEnemyModel()
{
	SAFE_DELETE(actor);
}

/**************************************
�X�V����
***************************************/
int BossEnemyModel::Update()
{
	actor->Update();
	return 0;
}

/**************************************
�`�揈��
***************************************/
void BossEnemyModel::Draw()
{
	actor->Draw();
}