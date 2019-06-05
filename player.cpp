//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : 渡邉良則
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "player_controller.h"
#include "UIdrawer.h"
#include "star.h"

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
PLAYER_CONTROLLER* pplayer_c;
OBJECT*	pstar;

LPD3DXFONT				g_pD3DXFont = NULL;			// フォントへのポインタ

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPlayer(void)
{
	pstar = GetStar();
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	player.g_posPlayer = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);
	player.g_rotPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	player.g_nCountAnim = 0;
	player.g_nPatternAnim = 0;

	player.move_wait = true;

	
	for (int i = 0; i < STAR_MAX; i++,pstar++) {
		player.targetpos[i] = pstar->position;
	}
	player.targetpos[CENTER] = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);

	// 頂点情報の作成
	MakeVertexPlayer();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile( pDevice,		// デバイスのポインタ
		TEXTURE_GAME_SAMPLE00,				// ファイルの名前
		&player.g_pD3DTexturePlayer );			// 読み込むメモリのポインタ

		// レンダリングステートパラメータの設定
	// 情報表示用フォントを設定
	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Terminal"), &g_pD3DXFont);


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{
	if(player.g_pD3DTexturePlayer != NULL )	//
	{	// テクスチャの開放
		player.g_pD3DTexturePlayer->Release();
		player.g_pD3DTexturePlayer = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{
	

	pplayer_c = GetPlayerController();

	// アニメーション

	//タイマー更新
	player.g_nCountAnim++;
	//TIME_ANIMATION = 100
	if ((player.g_nCountAnim % TIME_ANIMATION) == 1){
		//パターンの切り替え,ANIM_PATTERN_NUM=パターン数
		player.g_nPatternAnim = (player.g_nPatternAnim + 1) % ANIM_PATTERN_NUM;
		//パターンNoを渡してテクスチャ座標更新
		SetTexturePlayer(player.g_nPatternAnim);
	}

	//ベクトル
	D3DXVECTOR3 BtoPvec[MAX_LENGTH];
	//正規化
	D3DXVECTOR3 norBtoP;
	//距離
	FLOAT BtoPLen;

	SetPlayerTargetPosition(&player.goal);
	
	player.g_posPlayer = player.targetpos[player.goal];

	////移動処理
	//BtoPvec[player.movenum] = pnum[0]->g_posNum[player.movenum] - player.g_posPlayer;

	//D3DXVec3Normalize(&norBtoP, &BtoPvec[player.movenum]);

	//BtoPLen = D3DXVec3Length(&BtoPvec[player.movenum]);

	////引力
	//D3DXVECTOR3 attracsion = norBtoP * (FLOAT)2.0;


	////移動先への距離が2以上だった場合に移動
	////引力の数字に注意

	//if (BtoPLen >= 2) {
	//	player.g_posPlayer += attracsion;

	//}
	//else {
	//	//1以下の場合移動、入力を受け付けないフラグを解除（移動可）
	//	player.move_wait = true;
	//}


	//一筆書きできたか確認用、テキスト表示なので消す
	if (pplayer_c->flag == true) {
		pplayer_c->flag_count++;
		if (pplayer_c->flag_count >= 30) {
			pplayer_c->flag = false;
			pplayer_c->flag_count = 0;
		}
	}

	SetVertex();

}



//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	DrawTEXT();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture( 0, player.g_pD3DTexturePlayer );

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, player.g_vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点座標の設定
	player.g_vertexWk[0].vtx = D3DXVECTOR3(player.g_posPlayer.x, player.g_posPlayer.y, player.g_posPlayer.z);
	player.g_vertexWk[1].vtx = D3DXVECTOR3(player.g_posPlayer.x + TEXTURE_SAMPLE00_SIZE_X, player.g_posPlayer.y, player.g_posPlayer.z);
	player.g_vertexWk[2].vtx = D3DXVECTOR3(player.g_posPlayer.x, player.g_posPlayer.y +TEXTURE_SAMPLE00_SIZE_Y, player.g_posPlayer.z);
	player.g_vertexWk[3].vtx = D3DXVECTOR3(player.g_posPlayer.x + TEXTURE_SAMPLE00_SIZE_X, player.g_posPlayer.y + TEXTURE_SAMPLE00_SIZE_Y, player.g_posPlayer.z);

	// rhwの設定
	player.g_vertexWk[0].rhw =
	player.g_vertexWk[1].rhw =
	player.g_vertexWk[2].rhw =
	player.g_vertexWk[3].rhw = 1.0f;

	// 反射光の設定
	player.g_vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	player.g_vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	player.g_vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	player.g_vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	player.g_vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	player.g_vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	player.g_vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	player.g_vertexWk[3].tex = D3DXVECTOR2(0.2f, 1.0f);

	

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTexturePlayer( int cntPattern )
{
	// テクスチャ座標の設定
	//パターン番号からテクスチャ座標を計算,TEXTURE_PATTERN_DIVIDE_X = 8
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X;
	int y = cntPattern % TEXTURE_PATTERN_DIVIDE_X;
	//TEXTURE_PATTERN_DIVIDE_Y = 1
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y;
	//テクスチャ座標の更新
	player.g_vertexWk[0].tex = D3DXVECTOR2((float)(x)*sizeX, (float)(y)*sizeY);
	//右に1個増えるだけ（sizeX+sizeX）
	player.g_vertexWk[1].tex = D3DXVECTOR2((float)(x)*sizeX + sizeX, (float)(y)*sizeY);
	player.g_vertexWk[2].tex = D3DXVECTOR2((float)(x)*sizeX, (float)(y)*sizeY + sizeY);
	player.g_vertexWk[3].tex = D3DXVECTOR2((float)(x)*sizeX + sizeX, (float)(y)*sizeY + sizeY);
}

void SetVertex(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点座標の設定
	player.g_vertexWk[0].vtx = D3DXVECTOR3(player.g_posPlayer.x, player.g_posPlayer.y, player.g_posPlayer.z);
	player.g_vertexWk[1].vtx = D3DXVECTOR3(player.g_posPlayer.x + TEXTURE_SAMPLE00_SIZE_X, player.g_posPlayer.y, player.g_posPlayer.z);
	player.g_vertexWk[2].vtx = D3DXVECTOR3(player.g_posPlayer.x, player.g_posPlayer.y + TEXTURE_SAMPLE00_SIZE_Y, player.g_posPlayer.z);
	player.g_vertexWk[3].vtx = D3DXVECTOR3(player.g_posPlayer.x + TEXTURE_SAMPLE00_SIZE_X, player.g_posPlayer.y + TEXTURE_SAMPLE00_SIZE_Y, player.g_posPlayer.z);
}

void DrawTEXT(void)
{

	RECT rect2 = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	TCHAR str[256];

	if (pplayer_c->flag == true) {
		wsprintf(str, _T("\n\nbomb"));

		// テキスト描画
		g_pD3DXFont->DrawText(NULL, str, -1, &rect2, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	}
}

PLAYER* GetPlayer() {
	return &player;
}