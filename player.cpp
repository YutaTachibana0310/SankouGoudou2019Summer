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

#include "star.h"
#include "debugWindow.h"

/**************************************
マクロ定義
***************************************/
#define PLAYER_MODEL  "data/MODEL/airplane000.x"
#define PLAYER_MOVE		(120.0f)

#define TEXTURE_SAMPLE00_SIZE_X	(50) // テクスチャサイズ
#define TEXTURE_SAMPLE00_SIZE_Y	(50) // 同上

#define MAX_LENGTH (6)
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

	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rotDest= D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	/***************************************
	渡辺さん側の処理
	****************************************/
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	posPlayer = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);

	//移動先の星の位置を取得（中央だけは星の配置がないので個別指定）
	GetStarPosition(targetpos);
	targetpos[CENTER] = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);

	// 頂点情報の作成
	MakeVertexPlayer();

	return;

}

/***************************************
終了処理
****************************************/
void Player::Uninit()
{
	delete meshPlayer;

	/*************************************
	渡辺さん側の処理
	**************************************/
	if (D3DTexturePlayer != NULL)	//
	{	// テクスチャの開放
		D3DTexturePlayer->Release();
		D3DTexturePlayer = NULL;
	}
}
/****************************************
更新処理
*****************************************/
void Player::Update()
{
	/******************************
	渡邉さん皮の処理
	********************************/
	//移動先の指定
	SetPlayerTargetPosition(&goal);

	//移動処理（直接移動なので変更が必要ゴンさんよろしく）
	posPlayer = targetpos[goal];

	SetVertex();

	if (SetBomb() == true) {
		DebugText("bomb\n");
	}
}

/*****************************************
描画処理
******************************************/
void Player::Draw()
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, quatMatrixs, shadowMatrix,mtxWorld;
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

	/***************************************
	渡邉さん側の処理
	****************************************/
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, D3DTexturePlayer);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT Player::MakeVertexPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点座標の設定
	vertexWk[0].vtx = D3DXVECTOR3(posPlayer.x, posPlayer.y, posPlayer.z);
	vertexWk[1].vtx = D3DXVECTOR3(posPlayer.x + TEXTURE_SAMPLE00_SIZE_X, posPlayer.y, posPlayer.z);
	vertexWk[2].vtx = D3DXVECTOR3(posPlayer.x, posPlayer.y + TEXTURE_SAMPLE00_SIZE_Y, posPlayer.z);
	vertexWk[3].vtx = D3DXVECTOR3(posPlayer.x + TEXTURE_SAMPLE00_SIZE_X, posPlayer.y + TEXTURE_SAMPLE00_SIZE_Y, posPlayer.z);

	// rhwの設定
	vertexWk[0].rhw =
		vertexWk[1].rhw =
		vertexWk[2].rhw =
		vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWk[3].tex = D3DXVECTOR2(0.2f, 1.0f);



	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void Player::SetVertex(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点座標の設定
	vertexWk[0].vtx = D3DXVECTOR3(posPlayer.x, posPlayer.y, posPlayer.z);
	vertexWk[1].vtx = D3DXVECTOR3(posPlayer.x + TEXTURE_SAMPLE00_SIZE_X, posPlayer.y, posPlayer.z);
	vertexWk[2].vtx = D3DXVECTOR3(posPlayer.x, posPlayer.y + TEXTURE_SAMPLE00_SIZE_Y, posPlayer.z);
	vertexWk[3].vtx = D3DXVECTOR3(posPlayer.x + TEXTURE_SAMPLE00_SIZE_X, posPlayer.y + TEXTURE_SAMPLE00_SIZE_Y, posPlayer.z);
}

