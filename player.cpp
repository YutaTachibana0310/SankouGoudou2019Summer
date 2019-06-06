//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : 渡邉良則
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "PlayerController.h"

#include "star.h"
#include "debugWindow.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************

PLAYER player;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPlayer(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	player.posPlayer = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);
	player.rotPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	player.nCountAnim = 0;
	player.nPatternAnim = 0;

	//移動先の星の位置を取得（中央だけは星の配置がないので個別指定）
	GetStarPosition(player.targetpos);
	player.targetpos[CENTER] = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);

	// 頂点情報の作成
	MakeVertexPlayer();

	//注　2D画像なので3Dモデルに変更が必要、2Dは最終的に消すこと
	// テクスチャの読み込み
	D3DXCreateTextureFromFile( pDevice,		// デバイスのポインタ
		TEXTURE_GAME_SAMPLE00,				// ファイルの名前
		&player.D3DTexturePlayer );			// 読み込むメモリのポインタ

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{
	if(player.D3DTexturePlayer != NULL )	//
	{	// テクスチャの開放
		player.D3DTexturePlayer->Release();
		player.D3DTexturePlayer = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{

	//移動先の指定
	SetPlayerTargetPosition(&player.goal);

	//移動処理（直接移動なので変更が必要ゴンさんよろしく）
	player.posPlayer = player.targetpos[player.goal];

	SetVertex();

	if (SetBomb() == true) {
		DebugText("bomb\n");
	}

}



//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture( 0, player.D3DTexturePlayer );

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, player.vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点座標の設定
	player.vertexWk[0].vtx = D3DXVECTOR3(player.posPlayer.x, player.posPlayer.y, player.posPlayer.z);
	player.vertexWk[1].vtx = D3DXVECTOR3(player.posPlayer.x + TEXTURE_SAMPLE00_SIZE_X, player.posPlayer.y, player.posPlayer.z);
	player.vertexWk[2].vtx = D3DXVECTOR3(player.posPlayer.x, player.posPlayer.y +TEXTURE_SAMPLE00_SIZE_Y, player.posPlayer.z);
	player.vertexWk[3].vtx = D3DXVECTOR3(player.posPlayer.x + TEXTURE_SAMPLE00_SIZE_X, player.posPlayer.y + TEXTURE_SAMPLE00_SIZE_Y, player.posPlayer.z);

	// rhwの設定
	player.vertexWk[0].rhw =
	player.vertexWk[1].rhw =
	player.vertexWk[2].rhw =
	player.vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	player.vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	player.vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	player.vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	player.vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	player.vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	player.vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	player.vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	player.vertexWk[3].tex = D3DXVECTOR2(0.2f, 1.0f);

	

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetVertex(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点座標の設定
	player.vertexWk[0].vtx = D3DXVECTOR3(player.posPlayer.x, player.posPlayer.y, player.posPlayer.z);
	player.vertexWk[1].vtx = D3DXVECTOR3(player.posPlayer.x + TEXTURE_SAMPLE00_SIZE_X, player.posPlayer.y, player.posPlayer.z);
	player.vertexWk[2].vtx = D3DXVECTOR3(player.posPlayer.x, player.posPlayer.y + TEXTURE_SAMPLE00_SIZE_Y, player.posPlayer.z);
	player.vertexWk[3].vtx = D3DXVECTOR3(player.posPlayer.x + TEXTURE_SAMPLE00_SIZE_X, player.posPlayer.y + TEXTURE_SAMPLE00_SIZE_Y, player.posPlayer.z);
}
