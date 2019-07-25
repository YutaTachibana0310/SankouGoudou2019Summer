//=====================================
//
//�G�l�~�[�o���b�g����[EnemyBullet.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "EnemyBullet.h"
#include "Framework\ResourceManager.h"
#include "camera.h"
#include "GameParticleManager.h"
#include "EnemyBulletTrail.h"

/**************************************
�}�N����`
***************************************/
#define ENEMYBULLET_INIT_SPEED	(5.5f)

/**************************************
�R���X�g���N�^
***************************************/
EnemyBullet::EnemyBullet()
{
	ResourceManager::Instance()->GetPolygon(RESOURCE_ENEMYBULLET_TAG, &polygon);

	active = false;
}

/**************************************
�f�X�g���N�^
***************************************/
EnemyBullet::~EnemyBullet()
{
	polygon = NULL;
}

/**************************************
����������
***************************************/
void EnemyBullet::Init(D3DXVECTOR3 setPos, D3DXVECTOR3 target, int reachFrame)
{
	active = true;
	targetPos = target;
	cntFrame = reachFrame;

	transform.pos = setPos;

	velocity.x = RandomRangef(-1.0f, 1.0f);
	velocity.y = RandomRangef(-1.0f, 1.0f);
	velocity.z = 1.0f;
	D3DXVec3Normalize(&velocity, &velocity);
	velocity *= ENEMYBULLET_INIT_SPEED;

	BaseEmitter* emitter = GameParticleManager::Instance()->SetEnemyBulletTrail(&transform.pos);
	if (emitter != NULL)
		trail = static_cast<EnemyBulletTrailEmitter*>(emitter);
}

/**************************************
�I������
***************************************/
void EnemyBullet::Uninit()
{
	active = false;
	trail->active = false;
	trail = NULL;
}

/**************************************
�X�V����
***************************************/
void EnemyBullet::Update()
{
	if (!active)
		return;

	transform.Rotate(0.0f, 0.0f, 5.0f);
	
	D3DXVECTOR3 diff = targetPos - transform.pos;
	D3DXVECTOR3 acceleration = (diff - velocity * (float)cntFrame) * 2.0f / (float)(cntFrame * cntFrame);

	cntFrame--;

	if (cntFrame < 0)
		return;

	velocity += acceleration;

	transform.pos += velocity;
	trail->transform.pos = transform.pos;

}

/**************************************
�`�揈��
***************************************/
void EnemyBullet::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxWorld, mtxInvView;

	//���[���h�ϊ�
	mtxInvView = GetInvView();
	transform.CalcWorldMtx(&mtxWorld, &mtxInvView);
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	//�`��
	//polygon->Draw();
}