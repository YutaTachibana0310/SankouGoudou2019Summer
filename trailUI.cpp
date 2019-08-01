//=============================================================================
//
// 移動履歴画面処理 [trail.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "trailUI.h"
#include "UIdrawer.h"
#include "starUI.h"
#include "debugWindow.h"
#include "PlayerController.h"
#include "player.h"
#include <vector>

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TRAILPARTS_MAX	(6)
#define SIZE_TRAIL		(D3DXVECTOR3(100.0f,100.0f,0.0f))
#define POSITION_TRAIL	(D3DXVECTOR3(SCREEN_WIDTH/10*9,SCREEN_HEIGHT/10*5,0.0f))

//*****************************************************************************
// グローバル変数
//*****************************************************************************
Object	trail[TRAILPARTS_MAX];
int		historyMax;

//=============================================================================
// 初期化処理
//=============================================================================
void Trail::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャ読み込み
	object->LoadTexture(pDevice, ADRESS_TEXTURE_TRAIL_BG, &trail[TRAIL_BG]);
	object->LoadTexture(pDevice, ADRESS_TEXTURE_TRAIL_LINE_TOP_TO_LOWERLEFT, &trail[TRAIL_LINE_TOP_TO_LOWERLEFT]);
	object->LoadTexture(pDevice, ADRESS_TEXTURE_TRAIL_LINE_TOP_TO_LOWERRIGHT, &trail[TRAIL_LINE_TOP_TO_LOWERRIGHT]);
	object->LoadTexture(pDevice, ADRESS_TEXTURE_TRAIL_LINE_LOWERLELEFT_TO_MIDDLERIGHT, &trail[TRAIL_LINE_LOWERLEFT_TO_MIDDLERIGHT]);
	object->LoadTexture(pDevice, ADRESS_TEXTURE_TRAIL_LINE_LOWERRIGHT_TO_MIDDLELEFT, &trail[TRAIL_LINE_LOWERRIGHT_TO_MIDDLELEFT]);
	object->LoadTexture(pDevice, ADRESS_TEXTURE_TRAIL_LINE_MIDDLELEFT_TO_MIDDLERIGHT, &trail[TRAIL_LINE_MIDDLELEFT_TO_MIDDLERIGHT]);

	for (int i = 0; i < TRAILPARTS_MAX; i++)
	{
		object->InitialTexture(&trail[i]);
		//object->MakeVertexObject(&trail[i]);

		trail[i].position	= POSITION_TRAIL;
		trail[i].size		= SIZE_TRAIL;
		trail[i].rotation	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		object->SetColorObject(&trail[i], SET_COLOR_NOT_COLORED);
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void Trail::Uninit(void)
{
	for (int i = 0; i < TRAILPARTS_MAX; i++)
	{
		object->ReleaseTexture(&trail[i]);
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void Trail::Update(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void Trail::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// プレイヤーから受け取ったデータを入れる
	std::vector <int> drawHistory;
	GetPlayerMoveHistory(&drawHistory);

	// 先に背景を描画
	object->DrawObject(pDevice, &trail[TRAIL_BG]);
	object->SetVertexObject(&trail[TRAIL_BG]);

	// 要素数計算
	historyMax = drawHistory.size();

	for (int i = 0; i < historyMax; i++)
	{
		object->DrawObject(pDevice, &trail[drawHistory[i]]);
		object->SetVertexObject(&trail[drawHistory[i]]);
	}
}
