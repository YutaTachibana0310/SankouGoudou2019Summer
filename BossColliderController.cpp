//=====================================
//
//ボスコライダーコントローラ処理[BossColliderController.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "BossColliderController.h"
#include "Framework\ResourceManager.h"
#include "BossColliderGuide.h"
#include "BossEnemyModel.h"

using namespace std;
/**************************************
マクロ定義
***************************************/

/**************************************
コンストラクタ
***************************************/
BossColliderController::BossColliderController(BossEnemyModel& model) : posZ(500.0f), model(model)
{
	//ポリゴン準備
	ResourceManager::Instance()->MakePolygon("BossColliderEdge", "data/TEXTURE/Enemy/BossColliderEdge.png", D3DXVECTOR2(40.0f, 40.0f));
	ResourceManager::Instance()->MakePolygon("BossColliderLine", "data/TEXTURE/Enemy/BossCollider.png", D3DXVECTOR2(0.5f, 20.0f));
}

/**************************************
デストラクタ
***************************************/
BossColliderController::~BossColliderController()
{
	for (auto&& guide : guideList)
	{
		SAFE_DELETE(guide);
	}
	guideList.clear();

	for (auto&& collider : colliderList)
	{
		SAFE_DELETE(collider);
	}
	colliderList.clear();
}

/**************************************
更新処理
***************************************/
void BossColliderController::Update()
{
	for (auto&& guide : guideList)
	{
		guide->Update();
	}
}

/**************************************
描画処理
***************************************/
void BossColliderController::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
	pDevice->SetRenderState(D3DRS_ZENABLE, false);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	pDevice->SetRenderState(D3DRS_LIGHTING, false);

	for (auto&& guide : guideList)
	{
		guide->Draw();
	}

	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
	pDevice->SetRenderState(D3DRS_ZENABLE, true);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState(D3DRS_LIGHTING, true);
}

/**************************************
セット処理
***************************************/
void BossColliderController::SetCollider(const std::vector<int>& edgeList)
{
	const UINT EdgeMax = edgeList.size() - 1;
	for (UINT i = 0; i < EdgeMax; i++)
	{
		LineTrailModel model = LineTrailModel(edgeList[i], edgeList[i + 1]);
		guideList.push_back(new BossColliderGuide(model));
	
		TrailCollider *collider = new TrailCollider(TrailColliderTag::Enemy);
		collider->SetTrailIndex(model);
		collider->SetAddressZ(&posZ);

		//TODO：コライダーの有効化とオブザーバーの追加
		collider->AddObserver(this);
	}
}

/**************************************
全消去処理
***************************************/
void BossColliderController::DeleteAll()
{
	for (auto&& guide : guideList)
	{
		SAFE_DELETE(guide);
	}
	guideList.clear();

	for (auto&& collider : colliderList)
	{
		SAFE_DELETE(collider);
	}
	colliderList.clear();
}

/**************************************
当たり判定通知処理
***************************************/
void BossColliderController::OnNotified(ObserveSubject* notifier)
{
	model.OnDamage();
}