//=============================================================================
//
// テロップ背景処理 [telopBG.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "telopBG.h"
#include "Framework/Easing.h"
#include "debugWindow.h"
#include "battleStartTelop.h"
#include "UIdrawer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SIZE_TELOP_BG		(D3DXVECTOR3(SCREEN_WIDTH/4,50.0f,0.0f))
#define POSITION_TELOP_BG	(D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/10*8,0.0f))
#define INITIALVALUE_BG_PERCENTAGE (0.0f)
#define DURATION_OPEN_CLOSE (20.0f)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
Object	telopBG;
Easing<float> eTelopBG;
static float	percentage;

bool telopBGOpenActivated = false;
bool telopBGCloseActivated = false;

//=============================================================================
// 初期化処理
//=============================================================================
void TelopBG::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	object->LoadTexture(pDevice, ADRESS_TEXTURE_TELOP_BG, &telopBG);
	object->InitialTexture(&telopBG);
	object->MakeVertexObject(&telopBG);

	telopBG.position = POSITION_TELOP_BG;
	telopBG.size	 = SIZE_TELOP_BG;
	telopBG.rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	object->SetColorObject(&telopBG, SET_COLOR_NOT_COLORED);

	percentage = INITIALVALUE_BG_PERCENTAGE;
}

//=============================================================================
// 終了処理
//=============================================================================
void TelopBG::Uninit(void)
{
	object->ReleaseTexture(&telopBG);
}

//=============================================================================
// 更新処理
//=============================================================================
void TelopBG::Update(void)
{
	//　あふれ防止
	if (percentage < 0)
	{
		percentage = 0;
	}
	if (percentage > 1.0f)
	{
		percentage = 1.0f;
	}

	if (telopBGOpenActivated)
	{
		OpenTelopBG();
	}

	if (telopBGCloseActivated)
	{
		CloseTelopBG();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void TelopBG::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	object->DrawObject(pDevice, &telopBG);
	object->SetVertexTelopBG(&telopBG, percentage);
}

//=============================================================================
// 背景を開く処理
//=============================================================================
void TelopBG::OpenTelopBG(void)
{
	SetEasingValueTelopBGOpen();
	percentage = eTelopBG.GetEasingValue(object->GetCountObject(&telopBG, DURATION_OPEN_CLOSE), &telopBG.easingStart, &telopBG.easingGoal, InOutCubic);

	if(percentage >= telopBG.easingGoal)
	{
		telopBGOpenActivated = false;
		percentage = 1.0f;
		telopBG.countFrame = 0;
	}
}

//=============================================================================
// 背景を閉じる処理
//=============================================================================
void TelopBG::CloseTelopBG(void)
{
	SetEasingValueTelopBGClose();
	percentage = eTelopBG.GetEasingValue(object->GetCountObject(&telopBG ,DURATION_OPEN_CLOSE), &telopBG.easingStart, &telopBG.easingGoal, InOutCubic);

	if(percentage <= telopBG.easingGoal)
	{
		telopBGCloseActivated = false;
		percentage = 0.0f;
		telopBG.countFrame = 0;
	}
}

//=============================================================================
// 背景openイージングセット処理
//=============================================================================
void TelopBG::SetEasingValueTelopBGOpen(void)
{	
	telopBG.easingStart = INITIALVALUE_BG_PERCENTAGE;
	telopBG.easingGoal = 1.0f;
}

//=============================================================================
// 背景closeイージングセット処理
//=============================================================================
void TelopBG::SetEasingValueTelopBGClose(void)
{
	telopBG.easingStart = 1.0f;
	telopBG.easingGoal = INITIALVALUE_BG_PERCENTAGE;
}

//=============================================================================
// テロップ背景開始アクティベート処理
//=============================================================================
void TelopBG::AvctivateTelopBGOpen(void)
{
	telopBGOpenActivated = true;
}

//=============================================================================
// テロップ背景終了アクティベート処理
//=============================================================================
void TelopBG::AvctivateTelopBGClose(void)
{
	telopBGCloseActivated = true;
}

//=============================================================================
// テロップ背景開始アクティブ状態取得処理
//=============================================================================
bool TelopBG::GetTelopBGOpenActive(void)
{
	return telopBGOpenActivated;
}

//=============================================================================
// テロップ背景終了アクティブ状態取得処理
//=============================================================================
bool TelopBG::GetTelopBGCloseActive(void)
{
	return telopBGCloseActivated;
}