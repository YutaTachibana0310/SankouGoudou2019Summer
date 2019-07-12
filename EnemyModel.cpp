//=====================================
//
//�x�[�X�G�l�~�[���f������[EnemyModel.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "EnemyModel.h"
#include "GameParticleManager.h"

using namespace std;

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
EnemyModel::EnemyModel()
{
	collider = new TrailCollider(TrailColliderTag::Enemy);
	collider->AddObserver(this);
	pos.z = 250.0f;
	collider->SetAddressZ(&pos.z);
	active = false;
}

/**************************************
�f�X�g���N�^
***************************************/
EnemyModel::~EnemyModel()
{
	SAFE_DELETE(collider);
	
	for (auto& enemy : enemyList)
	{
		SAFE_DELETE(enemy);
	}
	enemyList.clear();
}

/**************************************
����������
***************************************/
void EnemyModel::Init(LineTrailModel model)
{
	this->model = model;
	collider->SetTrailIndex(model);
	cntFrame = 0;
	active = true;
}

/**************************************
�I������
***************************************/
void EnemyModel::Uninit()
{
	collider->active = false;
	active = false;
}

/**************************************
�`�揈��
***************************************/
void EnemyModel::Draw()
{
	for (auto& enemy : enemyList)
	{
		enemy->Draw();
	}

#ifdef TRAILCOLLIDER_USE_DEBUG
	TrailCollider::DrawCollider(collider);
#endif
}

/**************************************
�Փ˔���ʒm���V�[�o�[
***************************************/
void EnemyModel::OnNotified(ObserveSubject *notifier)
{
	//�������邷�ׂẴG�l�~�[�Ƀ_���[�W����
	for (auto& enemy : enemyList)
	{
		enemy->Uninit();
		GameParticleManager::Instance()->SetEnemyExplosion(&enemy->pos);
	}

	//��A�N�e�B�u��
	Uninit();
}