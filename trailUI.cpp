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
OBJECT	trail[TRAILPARTS_MAX];
int		trailHistoryCW[MOVESTACK_LENGTH];
int		trailHistoryCCW[MOVESTACK_LENGTH];
int		historyMax;

//*****************************************************************************
// プロトタイプ宣言
//******************************************************************************
bool CanDrawTrailLine(int startStar,int endStar);

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTrail(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャ読み込み
	LoadTexture(pDevice, ADRESS_TEXTURE_TRAIL_BG, &trail[TRAIL_BG]);
	LoadTexture(pDevice, ADRESS_TEXTURE_TRAIL_LINE_TOP_TO_LOWERLEFT, &trail[TRAIL_LINE_TOP_TO_LOWERLEFT]);
	LoadTexture(pDevice, ADRESS_TEXTURE_TRAIL_LINE_TOP_TO_LOWERRIGHT, &trail[TRAIL_LINE_TOP_TO_LOWERRIGHT]);
	LoadTexture(pDevice, ADRESS_TEXTURE_TRAIL_LINE_LOWERLELEFT_TO_MIDDLERIGHT, &trail[TRAIL_LINE_LOWERLEFT_TO_MIDDLERIGHT]);
	LoadTexture(pDevice, ADRESS_TEXTURE_TRAIL_LINE_LOWERRIGHT_TO_MIDDLELEFT, &trail[TRAIL_LINE_LOWERRIGHT_TO_MIDDLELEFT]);
	LoadTexture(pDevice, ADRESS_TEXTURE_TRAIL_LINE_MIDDLELEFT_TO_MIDDLERIGHT, &trail[TRAIL_LINE_MIDDLELEFT_TO_MIDDLERIGHT]);

	for (int i = 0; i < TRAILPARTS_MAX; i++)
	{
		InitialTexture(&trail[i]);
		MakeVertexObject(&trail[i]);

		trail[i].position	= POSITION_TRAIL;
		trail[i].size		= SIZE_TRAIL;
		trail[i].rotation	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		SetColorObject(&trail[i], SET_COLOR_NOT_COLORED);
	}

	// 配列を要素と関係ない値で初期化	
	for (int i = 0; i < MOVESTACK_LENGTH; i++)
	{
		trailHistoryCW[i] = { 8 };
		trailHistoryCCW[i] = { 8 };
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTrail(void)
{
	for (int i = 0; i < TRAILPARTS_MAX; i++)
	{
		ReleaseTexture(&trail[i]);
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTrail(void)
{
	if (SetBomb() == true)
	{
		for (int i = 0; i < MOVESTACK_LENGTH; i++) 
		{
			trailHistoryCW[i] = { INITIAL_ARRAY_NUMBER };
			trailHistoryCCW[i] = { INITIAL_ARRAY_NUMBER };
		}
	}

	GetMove_StackCW(trailHistoryCW);
	GetMove_StackCCW(trailHistoryCCW);
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTrail(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 先に背景を描画
	DrawObject(pDevice, trail[TRAIL_BG]);
	SetVertexObject(&trail[TRAIL_BG]);

	// それぞれtrueだったらラインを描画
	if (CanDrawTrailLine(TOP,LOWER_LEFT) == true)
	{
		DrawObject(pDevice, trail[TRAIL_LINE_TOP_TO_LOWERLEFT]);
		SetVertexObject(&trail[TRAIL_LINE_TOP_TO_LOWERLEFT]);
	}
	if (CanDrawTrailLine(TOP, LOWER_RIGHT) == true)
	{
		DrawObject(pDevice, trail[TRAIL_LINE_TOP_TO_LOWERRIGHT]);
		SetVertexObject(&trail[TRAIL_LINE_TOP_TO_LOWERRIGHT]);
	}
	if (CanDrawTrailLine(LOWER_LEFT, MIDDLE_RIGHT) == true)
	{
		DrawObject(pDevice, trail[TRAIL_LINE_LOWERLEFT_TO_MIDDLERIGHT]);
		SetVertexObject(&trail[TRAIL_LINE_LOWERLEFT_TO_MIDDLERIGHT]);
	}
	if (CanDrawTrailLine(LOWER_RIGHT, MIDDLE_LEFT) == true)
	{
		DrawObject(pDevice, trail[TRAIL_LINE_LOWERRIGHT_TO_MIDDLELEFT]);
		SetVertexObject(&trail[TRAIL_LINE_LOWERRIGHT_TO_MIDDLELEFT]);
	}
	if (CanDrawTrailLine(MIDDLE_LEFT, MIDDLE_RIGHT) == true)
	{
		DrawObject(pDevice, trail[TRAIL_LINE_MIDDLELEFT_TO_MIDDLERIGHT]);
		SetVertexObject(&trail[TRAIL_LINE_MIDDLELEFT_TO_MIDDLERIGHT]);
	}
}

void DrawTrail(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// プレイヤーから受け取ったデータを入れる
	std::vector <int> drawHistory;

	// 先に背景を描画
	DrawObject(pDevice, trail[TRAIL_BG]);
	SetVertexObject(&trail[TRAIL_BG]);

	// 要素数計算
	historyMax = drawHistory.size();

	for (int i = 0; i < historyMax; i++)
	{
		DrawObject(pDevice, trail[drawHistory[i]]);
		SetVertexObject(&trail[drawHistory[i]]);
	}
}

//=============================================================================
// 描画可能判定処理 (可能だったらtrueを返す)
//=============================================================================
bool CanDrawTrailLine(int startStar, int endStar)
{
	bool canDraw;
	int	 searchFailedCount = 0;
	int	 searchSuccessCount = 0;

	for (int i = 0; i < MOVESTACK_LENGTH; i++)
	{
		// 配列の中で連続しているor配列の最後と最初で連続していたら描画 (全ての組み合わせでチェック)
		if ((trailHistoryCW[i] == startStar && trailHistoryCW[i + 1] == endStar)
			|| (trailHistoryCW[i] == endStar && trailHistoryCW[i + 1] == startStar)
			|| (trailHistoryCCW[i] == startStar && trailHistoryCCW[i + 1] == endStar)
			|| (trailHistoryCCW[i] == endStar && trailHistoryCCW[i + 1] == startStar))
		{
			canDraw = true;
			searchSuccessCount++;
		}
		else
		{
			searchFailedCount++;
		}

		if (searchFailedCount >= MOVESTACK_LENGTH)
		{
			canDraw = false;
			searchFailedCount = 0;
		}

		if (searchSuccessCount + searchFailedCount >= MOVESTACK_LENGTH)
		{
			searchSuccessCount = 0;
			searchFailedCount = 0;
		}
	}
	return canDraw;
}