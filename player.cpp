//=====================================
//
//プレイヤー処理[player.cpp]
//Author:GP12B332 12 権頭
//
//=====================================
#include "player.h"

#include "main.h"
#include "player.h"
#include "PlayerController.h"

#include "starUI.h"
#include "debugWindow.h"

/**************************************
マクロ定義
***************************************/
#define PLAYER_MODEL  "data/MODEL/airplane000.x"

/**************************************
構造体定義
***************************************/


/**************************************
グローバル変数
***************************************/

/**************************************
プロトタイプ宣言
***************************************/


/*************************************
初期化処理
**************************************/
void Player::Init()
{
	meshPlayer = new MeshContainer();
	meshPlayer->Load(PLAYER_MODEL);

	pos = PLAYER_CENTER;
	scl = D3DXVECTOR3(2.0f, 2.0f, 2.0f);
	rot = D3DXVECTOR3(0.0f, 59.7f, 0.0f);

	trail = new PlayerTrail();

	return;
}

/***************************************
終了処理
****************************************/
void Player::Uninit()
{
	delete meshPlayer;
	delete trail;

}
/****************************************
更新処理
*****************************************/
void Player::Update()
{

	if (SetBomb() == true) {
		DebugText("bomb\n");
	}

	trail->Update();
}

/*****************************************
描画処理
******************************************/
void Player::Draw()
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, quatMatrixs, shadowMatrix, mtxWorld;
	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	// スケールを反映
	D3DXMatrixScaling(&mtxScl, scl.y, scl.x, scl.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	meshPlayer->Draw();
	trail->Draw();

}