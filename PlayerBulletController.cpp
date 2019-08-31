//=====================================
//
//プレイヤーコントローラ処理[PlayerBulletController.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "PlayerBulletController.h"
#include <algorithm>
#include "sound.h"

using namespace std;
/**************************************
マクロ定義
***************************************/

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/

/**************************************
コンストラクタ
***************************************/
PlayerBulletController::PlayerBulletController()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	const char* TextureName = "data/TEXTURE/Player/PlayerBullet.png";

	texture = CreateTextureFromFile((LPSTR)TextureName, pDevice);
}

/**************************************
デストラクタ
***************************************/
PlayerBulletController::~PlayerBulletController()
{
	for (auto &bullet : bulletContainer)
	{
		SAFE_DELETE(bullet);
	}
	bulletContainer.clear();

	SAFE_RELEASE(texture);
}

/**************************************
初期化処理
***************************************/
void PlayerBulletController::Init()
{

}

/**************************************
終了処理
***************************************/
void PlayerBulletController::Uninit()
{
	for (auto &bullet : bulletContainer)
	{
		bullet->Uninit();
	}
}

/**************************************
更新処理
***************************************/
void PlayerBulletController::Update()
{
	//バレットの破壊確認
	for (auto &bullet : bulletContainer)
	{
		if (bullet->isDestroyed)
			bullet->Uninit();
	}

	//更新
	for (auto &bullet : bulletContainer)
	{
		bullet->Update();
	}
}

/**************************************
描画処理
***************************************/
void PlayerBulletController::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetFVF(FVF_VERTEX_3D);

	pDevice->SetTexture(0, texture);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	pDevice->SetRenderState(D3DRS_LIGHTING, false);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

	for (auto &bullet : bulletContainer)
	{
		bullet->Draw();
	}

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	pDevice->SetRenderState(D3DRS_LIGHTING, true);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}

/**************************************
バレットセット処理
***************************************/
void PlayerBulletController::SetPlayerBullet(LineTrailModel model)
{
	auto itr = find_if(bulletContainer.begin(), bulletContainer.end(),[](PlayerBullet* bullet)
	{
		return !bullet->active;
	});

	if (itr != bulletContainer.end())
	{
		(*itr)->Init(model);
		//ショットSE
		Sound::GetInstance()->SetPlaySE(PLAYERSHOT, true, 0.05f);
	}
	else
	{
		PlayerBullet *bullet = new PlayerBullet();
		bullet->Init(model);
		bulletContainer.push_back(bullet);
		//ショットSE
		Sound::GetInstance()->SetPlaySE(PLAYERSHOT, true, 0.05f);
	}
}