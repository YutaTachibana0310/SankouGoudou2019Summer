//=====================================
//
//�G�l�~�[�o���b�g���f������[EnemyBulletModel.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "EnemyBulletModel.h"
#include "EnemyBullet.h"

/**************************************
�}�N����`
***************************************/
#define ENEMYBULLET_REACH_DEFAULT		(90)

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

	collider->SetTrailIndex(target);

	bullets.reserve(emitters.size());

	D3DXVECTOR3 edgeR, edgeL;
	target.GetEdgePos(&edgeR, &edgeL);
	D3DXVECTOR3 diff = edgeL - edgeR;
	diff /= emitters.size() - 1;

	D3DXVECTOR3 targetPos = edgeR;
	for (UINT cnt = 0; cnt < emitters.size(); cnt++)
	{
		bullets.push_back(new EnemyBullet());
		bullets[cnt]->Init(emitters[cnt], targetPos, ENEMYBULLET_REACH_DEFAULT);
		targetPos += diff;
	}

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
}

/**************************************
�X�V����
***************************************/
void EnemyBulletModel::Update()
{
	for (auto& bullet : bullets)
	{
		bullet->Update();
	}

	cntFrame++;
}

/**************************************
�`�揈��
***************************************/
void EnemyBulletModel::Draw()
{
	for (auto& bullet : bullets)
	{
		bullet->Draw();
	}
}


