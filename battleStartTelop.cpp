//=============================================================================
//
// バトルスタートテロップ処理 [battleStartTelop.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "battleStartTelop.h"
#include "UIdrawer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SIZE_BATTLE_START_TELOP		(D3DXVECTOR3(SCREEN_WIDTH/4,50.0f,0.0f))
#define POSITION_BATTLE_START_TELOP	(D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/10*8,0.0f))

//*****************************************************************************
// グローバル変数
//*****************************************************************************
OBJECT	battleStartTelop;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBattleStartTelop(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	LoadTexture(pDevice, ADRESS_TEXTURE_BATTLE_START_TELOP, &battleStartTelop);
	InitialTexture(&battleStartTelop);
	MakeVertexObject(&battleStartTelop);

	battleStartTelop.position = POSITION_BATTLE_START_TELOP;
	battleStartTelop.size = SIZE_BATTLE_START_TELOP;
	battleStartTelop.rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	SetColorObject(&battleStartTelop, SET_COLOR_NOT_COLORED);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBattleStartTelop(void)
{
	ReleaseTexture(&battleStartTelop);
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBattleStartTelop()
{
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBattleStartTelop(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	DrawObject(pDevice, battleStartTelop);
	SetVertexObject(&battleStartTelop);
}
