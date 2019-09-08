//=====================================
//
//�G�l�~�[�o���b�g���f������[EnemyBulletModel.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "EnemyBulletModel.h"
#include "EnemyBullet.h"
#include "GameParticleManager.h"
#include "Framework\BoxCollider3D.h"

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

	const D3DXVECTOR3 ColliderSize = D3DXVECTOR3(10.0f, 10.0f, 10.0f);
	colliderL = new BoxCollider3D(BoxCollider3DTag::EnemyBullet, &edgeL, ColliderSize);
	colliderR = new BoxCollider3D(BoxCollider3DTag::EnemyBullet, &edgeR, ColliderSize);
	colliderL->active = false;
	colliderR->active = false;

	effect = NULL;
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
	SAFE_DELETE(colliderL);
	SAFE_DELETE(colliderR);
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

	reachFrame = ENEMYBULLET_REACH_DEFAULT;
	active = true;
}

/**************************************
����������
***************************************/
void EnemyBulletModel::Init(std::vector<D3DXVECTOR3> emitters, LineTrailModel target, int duration, const D3DXVECTOR3& scale)
{
	cntFrame = 0;

	targetLine = target;
	collider->SetTrailIndex(target);

	bullets.reserve(emitters.size());

	//�e�̒��e�_���v�Z
	target.GetEdgePos(&edgeR, &edgeL);
	D3DXVECTOR3 diff = edgeL - edgeR;
	diff /= (float)(emitters.size() + 1);


	D3DXVECTOR3 targetPos = edgeR + diff;
	for (UINT cnt = 0; cnt < emitters.size(); cnt++)
	{
		bullets.push_back(new EnemyBullet());
		bullets[cnt]->Init(emitters[cnt], targetPos, duration, scale);
		targetPos += diff;
	}

	reachFrame = duration;
	active = true;
}

/**************************************
�I������
***************************************/
void EnemyBulletModel::Uninit()
{
	collider->active = false;
	colliderL->active = false;
	colliderR->active = false;

	for (auto& bullet : bullets)
	{
		SAFE_DELETE(bullet);
	}
	bullets.clear();

	active = false;

	effect = NULL;
}

/**************************************
�X�V����
***************************************/
void EnemyBulletModel::Update()
{
	if (!active)
		return;

	cntFrame++;

	//�o���b�g�̍X�V
	for (auto& bullet : bullets)
	{
		bullet->Update();
	}

	//���e�����Ȃ瓖���蔻����A�N�e�B�u��
	if (cntFrame == reachFrame)
	{
		//�[�̃{�b�N�X�R���C�_�[���A�N�e�B�u��
		colliderL->active = true;
		colliderR->active = true;

		//TrailCollider���A�N�e�B�u��
		collider->active = true;
		effect = GameParticleManager::Instance()->SetEnemyBulletEffect(targetLine);
	}

	//�I������
	if (cntFrame == reachFrame + ENeMYBULLET_EFFECTIVE_FRAME)
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

	TrailCollider::DrawCollider(collider);
	BoxCollider3D::DrawCollider(colliderL);
	BoxCollider3D::DrawCollider(colliderR);
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

	if (effect != NULL)
		effect->Uninit();

	Uninit();
}