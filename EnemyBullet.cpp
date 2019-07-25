//=====================================
//
//エネミーバレット処理[EnemyBullet.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "EnemyBullet.h"
#include "Framework\ResourceManager.h"
#include "camera.h"

/**************************************
マクロ定義
***************************************/
#define ENEMYBULLET_INIT_SPEED	(5.0f)

/**************************************
コンストラクタ
***************************************/
EnemyBullet::EnemyBullet()
{
	ResourceManager::Instance()->GetPolygon(RESOURCE_ENEMYBULLET_TAG, &polygon);

	active = false;
}

/**************************************
デストラクタ
***************************************/
EnemyBullet::~EnemyBullet()
{
	polygon = NULL;
}

/**************************************
初期化処理
***************************************/
void EnemyBullet::Init(D3DXVECTOR3 setPos, D3DXVECTOR3 target, int reachFrame)
{
	active = true;
	targetPos = target;
	cntFrame = 0;
	this->reachFrame = reachFrame;

	transform.pos = setPos;

	velocity.x = RandomRangef(-1.0f, 1.0f);
	velocity.y = RandomRangef(-1.0f, 1.0f);
	velocity.z = 0.0f;
	D3DXVec3Normalize(&velocity, &velocity);
	velocity *= ENEMYBULLET_INIT_SPEED;
}

/**************************************
終了処理
***************************************/
void EnemyBullet::Uninit()
{
	active = false;
}

/**************************************
更新処理
***************************************/
void EnemyBullet::Update()
{
	if (!active)
		return;
	
	D3DXVECTOR3 diff = targetPos - transform.pos;
	D3DXVECTOR3 acceleration = (diff - velocity * cntFrame) * 2.0f / (float)(cntFrame * cntFrame);

	cntFrame--;

	if (cntFrame < 0)
		return;

	velocity += acceleration;

	transform.pos += velocity;
}

/**************************************
描画処理
***************************************/
void EnemyBullet::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxWorld, mtxInvView;

	//ワールド変換
	mtxInvView = GetInvView();
	transform.CalcWorldMtx(&mtxWorld, &mtxInvView);
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	//描画
	polygon->Draw();
}