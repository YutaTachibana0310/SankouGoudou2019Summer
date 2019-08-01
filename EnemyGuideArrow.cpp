//=====================================
//
//エネミーガイドアロー処理[EnemyGuideArrow.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "EnemyGuideArrow.h"
#include "Framework\Easing.h"
#include "Framework\ResourceManager.h"

/**************************************
マクロ定義
***************************************/
#define ENEMYGUIDEARROW_LIFEFRAME		(60)
#define ENEMYGUIDEARROW_INTERVAL		(2)

#define ENEMYGUIDEARROW_BASE_VECTOR		(&D3DXVECTOR3(0.0f, 1.0f, 0.0f))

/**************************************
EnemyGuideArrowコンストラクタ
***************************************/
EnemyGuideArrow::EnemyGuideArrow()
{
	ResourceManager::Instance()->GetPolygon("EnemyGuideArrow", &polygon);
	cntFrame = 0;
	active = false;
}

/**************************************
EnemyGuideArrowデストラクタ
***************************************/
EnemyGuideArrow::~EnemyGuideArrow()
{
	polygon = NULL;
}

/**************************************
EnemyGuideArrow初期化処理
***************************************/
void EnemyGuideArrow::Init()
{
	cntFrame = 0;
	active = true;
}

/**************************************
EnemyGuideArrow終了処理
***************************************/
void EnemyGuideArrow::Uninit()
{
	active = false;
}

/**************************************
EnemyGuideArrow更新処理
***************************************/
void EnemyGuideArrow::Update()
{
	if (!active)
		return;

	cntFrame++;

	if (cntFrame == ENEMYGUIDEARROW_LIFEFRAME)
		active = false;
}

/**************************************
EnemyGuideArrow描画処理
***************************************/
void EnemyGuideArrow::Draw()
{
	if (!active)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxWorld;
	transform.CalcWorldMtx(&mtxWorld);

	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	polygon->Draw();
}

/**************************************
EnemyGuideArrowEmitterコンストラクタ
***************************************/
EnemyGuideArrowEmitter::EnemyGuideArrowEmitter()
{
	int containerSize = ENEMYGUIDEARROW_DURATION / ENEMYGUIDEARROW_INTERVAL;
	arrowContainer.resize(containerSize);
	for (auto& arrow : arrowContainer)
	{
		arrow = new EnemyGuideArrow();
	}

	active = false;
}

/**************************************
EnemyGuideArrowEmitterデストラクタ
***************************************/
EnemyGuideArrowEmitter::~EnemyGuideArrowEmitter()
{
	SAFE_DELETE_VECTOR(arrowContainer);
}

/**************************************
EnemyGuideArrowEmitter初期化処理
***************************************/
void EnemyGuideArrowEmitter::Init(D3DXVECTOR3 start, D3DXVECTOR3 end)
{
	cntFrame = 0;
	cntArrow = 0;
	active = true;

	this->start = start;
	this->end = end;

	D3DXVECTOR3 diff = end - start;
	D3DXVec3Normalize(&diff, &diff);

	int dir = diff.x < 0 ? 1 : -1;

	transform.rot.z = dir * acosf(D3DXVec3Dot(ENEMYGUIDEARROW_BASE_VECTOR, &diff))               ;
}

/**************************************
EnemyGuideArrowEmitter終了処理
***************************************/
void EnemyGuideArrowEmitter::Uninit()
{
	active = false;

	for (auto& arrow : arrowContainer)
	{
		arrow->Uninit();
	}

}

/**************************************
EnemyGuideArrowEmitter更新処理
***************************************/
void EnemyGuideArrowEmitter::Update()
{
	if (!active)
		return;

	cntFrame++;

	float t = (float)cntFrame / ENEMYGUIDEARROW_DURATION;
	transform.pos = Easing<D3DXVECTOR3>::GetEasingValue(t, &start, &end, EasingType::Linear);

	if (cntFrame < ENEMYGUIDEARROW_DURATION && cntFrame % ENEMYGUIDEARROW_INTERVAL == 0)
	{
		arrowContainer[cntArrow]->transform = transform;
		arrowContainer[cntArrow]->Init();
		cntArrow++;
	}

	if (cntFrame >= ENEMYGUIDEARROW_DURATION)
	{
		bool isArrowAlive = false;
		for (auto& arrow : arrowContainer)
		{
			isArrowAlive |= arrow->active;
		}

		if (!isArrowAlive)
			Uninit();
	}

	for (auto& arrow : arrowContainer)
	{
		arrow->Update();
	}
}

/**************************************
EnemyGuideArrowEmitter描画処理
***************************************/
void EnemyGuideArrowEmitter::Draw()
{
	if (!active)
		return;

	for(auto& arrow : arrowContainer)
	{
		arrow->Draw();
	}
}