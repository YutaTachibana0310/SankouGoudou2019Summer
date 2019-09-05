//=============================================================================
//
// 移動履歴画面処理 [trail.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "UIdrawer.h"
#include "starUI.h"
#include "debugWindow.h"
#include "PlayerController.h"
#include "player.h"
#include <vector>
#include "trailUI.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SIZE_TRAIL		(D3DXVECTOR3(100.0f,100.0f,0.0f))
#define POSITION_TRAIL	(D3DXVECTOR3(SCREEN_WIDTH/10*9,SCREEN_HEIGHT/10*3,0.0f))

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
Trail::Trail()
{
	for (int i = 0; i < TRAILPARTS_MAX; i++)
	{
		trail[i] = new Object();

		// テクスチャ読み込み
		trail[i]->LoadTexture(texPath[i]);
		trail[i]->MakeVertex();

		trail[i]->position = POSITION_TRAIL;
		trail[i]->size = SIZE_TRAIL;
		trail[i]->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		trail[i]->SetColorObject(SET_COLOR_NOT_COLORED);
	}
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
Trail::~Trail()
{
	for (int i = 0; i < TRAILPARTS_MAX; i++)
	{
		delete trail[i];
		trail[i] = NULL;
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
	// プレイヤーから受け取ったデータを入れる
	std::vector <int> drawHistory;
	GetPlayerMoveHistory(&drawHistory);

	// 先に背景を描画
	trail[TRAIL_BG]->Draw();
	trail[TRAIL_BG]->SetVertex();

	// 要素数計算
	historyMax = drawHistory.size();

	for (int i = 0; i < historyMax; i++)
	{
		trail[drawHistory[i]]->Draw();
		trail[drawHistory[i]]->SetVertex();
	}
}
