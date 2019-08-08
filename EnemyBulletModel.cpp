//=====================================
//
//�G�l�~�[�o���b�g���f������[EnemyBulletModel.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "EnemyBulletModel.h"
#include "EnemyBullet.h"
#include "GameParticleManager.h"

/**************************************
�}�N����`
***************************************/
#define ENEMYBULLET_REACH_DEFAULT		(45)
#define ENeMYBULLET_EFFECTIVE_FRAME		(120)

/**************************************
�R���X�g���N�^
***************************************/
EnemyBulletModel::EnemyBulletModel()
{
	active = false;
	posZ = 0.0f;

	collider = new TrailCollider(TrailColliderTag::EnemyBullet);
	collider->SetAddressZ(&posZ);
	collider->active = false;
}

/**************************************
�f�X�g���N�^
***************************************/
EnemyBulletModel::~EnemyBulletModel()
{
	for (auto& bullet : bullets)
	{
		SAFE_DELETE(bullet);
	}
	bullets.clear();

	SAFE_DELETE(collider);
}

/**************************************
����������
***************************************/
void EnemyBulletModel::Init(std::vector<D3DXVECTOR3> emitters, LineTrailModel target)
{
	cntFrame = 0;

	targetLine = target;
	collider->SetTrailIndex(target);

	bullets.reserve(emitters.size());

	//�e�̒��e�_���v�Z
	D3DXVECTOR3 edgeR, edgeL;
	target.GetEdgePos(&edgeR, &edgeL);
	D3DXVECTOR3 diff = edgeL - edgeR;
	diff /= (float)(emitters.size() + 1);


	D3DXVECTOR3 targetPos = edgeR + diff;
	for (UINT cnt = 0; cnt < emitters.size(); cnt++)
	{
		bullets.push_back(new EnemyBullet());
		bullets[cnt]->Init(emitters[cnt], targetPos, ENEMYBULLET_REACH_DEFAULT);
		targetPos += diff;
	}

	active = true;
}

/**************************************
�I������
***************************************/
void EnemyBulletModel::Uninit()
{
	collider->active = false;

	for (auto& bullet : bullets)
	{
		SAFE_DELETE(bullet);
	}
	bullets.clear();

	active = false;
}

/**************************************
�X�V����
***************************************/
void EnemyBulletModel::Update()
{
	if (!active)
		return;

	cntFrame++;

	for (auto& bullet : bullets)
	{
		bullet->Update();
	}

	if (cntFrame == ENEMYBULLET_REACH_DEFAULT)
	{
		collider->active = true;
		GameParticleManager::Instance()->SetEnemyBulletEffect(targetLine);
	}

	if (cntFrame == ENeMYBULLET_EFFECTIVE_FRAME + ENEMYBULLET_REACH_DEFAULT)
	{
		Uninit();
	}
}

/**************************************
�`�揈��
***************************************/
void EnemyBulletModel::Draw()
{
	if (!active)
		return;

	for (auto& bullet : bullets)
	{
		bullet->Draw();
	}

	//TrailCollider::DrawCollider(collider);
}

/**************************************
��A�N�e�B�u����
***************************************/
void EnemyBulletModel::Disable()
{
	for (auto& bullet : bullets)
	{
		if (!bullet->active)
			continue;

		GameParticleManager::Instance()->SetEnemyBulletExplosion(&bullet->transform.pos);
		bullet->Uninit();
	}

	Uninit();
}