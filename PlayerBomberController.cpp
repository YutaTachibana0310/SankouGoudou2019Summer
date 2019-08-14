//============================================================
//
//プレイヤーコントローラ処理[PlayerBomberController.cpp]
//Author: 権頭
//
//============================================================
#include "PlayerBomberController.h"
#include <algorithm>
#include "Framework\ResourceManager.h"
#include "enemy.h"
#include "GameParticleManager.h"
#include "debugWindow.h"

using namespace std;

/*********************************************************
マクロ定義
**********************************************************/
#define BOMBER_SIZE					(20.0f)
#define BOMBER_STOCK_INTERVAL		(600)
#define BOMBER_STOCK_MAX			(1)

/********************************************************
構造体定義
*********************************************************/

/*********************************************************
グローバル変数
**********************************************************/

/*********************************************************
コンストラクタ
**********************************************************/
PlayerBomberController::PlayerBomberController()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	const char* TextureName = "data/TEXTURE/Effect/PlayerBulletParticle.png";

	texture = CreateTextureFromFile((LPSTR)TextureName, pDevice);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)* NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &vtxBuff, 0);
	
	VERTEX_3D *pVtx;
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].vtx = D3DXVECTOR3(-BOMBER_SIZE / 2.0f, BOMBER_SIZE / 2.0f, 0.0f);
	pVtx[1].vtx = D3DXVECTOR3(BOMBER_SIZE / 2.0f, BOMBER_SIZE / 2.0f, 0.0f);
	pVtx[2].vtx = D3DXVECTOR3(-BOMBER_SIZE / 2.0f, -BOMBER_SIZE / 2.0f, 0.0f);
	pVtx[3].vtx = D3DXVECTOR3(BOMBER_SIZE / 2.0f, -BOMBER_SIZE / 2.0f, 0.0f);

	//反射光の設定
	pVtx[0].diffuse =
		pVtx[1].diffuse =
		pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//
	pVtx[0].nor =
		pVtx[1].nor =
		pVtx[2].nor =
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//テクスチャ座標の設定

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	vtxBuff->Unlock();

	//ストックインターバル初期化
	stockInterval = BOMBER_STOCK_INTERVAL;
	stock = 1;
}

/*********************************************************
デストラクタ
**********************************************************/
PlayerBomberController::~PlayerBomberController()
{
	for (auto &bomber : bomberContainer)
	{
		SAFE_DELETE(bomber);
	}
	bomberContainer.clear();

	SAFE_RELEASE(texture);
	SAFE_RELEASE(vtxBuff);
}

/*********************************************************
初期化処理
**********************************************************/
void PlayerBomberController::Init()
{

}


/*********************************************************
終了処理
**********************************************************/
void PlayerBomberController::Uninit()
{
	for (auto& bomber : bomberContainer)
	{
		bomber->Uninit();
	}
}

/*********************************************************
更新処理
**********************************************************/
void PlayerBomberController::Update()
{
	//更新
	for (auto &bomber : bomberContainer)
	{
		bomber->Update();
	}

	//ストックインターバルを更新
	stockInterval = Min(BOMBER_STOCK_INTERVAL, stockInterval + 1);

	DebugLog("BombStock : %d", stock);
	DebugLog("BomInterval : %d", stockInterval);
}

/*********************************************
描画処理
**********************************************/
void PlayerBomberController::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//vtxbuffをセット

	pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(VERTEX_3D));

	pDevice->SetFVF(FVF_VERTEX_3D);

	pDevice->SetTexture(0, texture);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	pDevice->SetRenderState(D3DRS_LIGHTING, false);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

	for (auto &bomber : bomberContainer)
	{
		bomber->Draw();
	}

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	pDevice->SetRenderState(D3DRS_LIGHTING, true);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);

}

/***************************************************
ボムセット処理
***************************************************/
void PlayerBomberController::SetPlayerBomber(list<Enemy*>targetList, D3DXVECTOR3 initpos)
{
	D3DXVECTOR3 setPos = initpos + D3DXVECTOR3(0.0f, 10.0f, 50.0f);
	float rotAngle = D3DXToRadian(360.0f / targetList.size());
	float radian = 0.0f;

	for (auto &target : targetList)
	{
		D3DXVECTOR3 dir;
		ZeroMemory(&dir, sizeof(dir));
		dir.x = sinf(radian);
		dir.y = cosf(radian);

		auto itr = find_if(bomberContainer.begin(), bomberContainer.end(), [](PlayerBomber* bomber)
		{
			return !bomber->active;
		});

		if (itr != bomberContainer.end())
		{
			PlayerBomber* bomber = *itr;
			bomber->Init(dir);
			bomber->Set(target, setPos);
			target->AddTargeter(bomber);
		}
		else
		{
			PlayerBomber *bomber = new PlayerBomber();
			bomber->Init(dir);
			bomber->Set(target, setPos);
			bomberContainer.push_back(bomber);
			target->AddTargeter(bomber);
		}

		radian += rotAngle;
	}

	//ストックを消費
	stock--;
	stockInterval = 0;

	//発射エフェクトセット
	GameParticleManager::Instance()->SetBomberFire(&setPos);
}

/***************************************************
ストックの可否判定
***************************************************/
bool PlayerBomberController::CanStock()
{
	//return stockInterval >= BOMBER_STOCK_INTERVAL;
	return true;
}

/***************************************************
ボム発射の可否判定
***************************************************/
bool PlayerBomberController::CanSet()
{
	if (stock <= 0)
		return false;

	if (stockInterval < BOMBER_STOCK_INTERVAL)
		return false;

	return true;
}

/***************************************************
ストック追加処理
***************************************************/
void PlayerBomberController::AddStock()
{
	stock = Min(stock + 1, BOMBER_STOCK_MAX);
	//stockInterval = 0;
}
