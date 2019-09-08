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
// グローバル変数
//*****************************************************************************
bool telopBGOpenActivated = false;
bool telopBGCloseActivated = false;

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
TelopBG::TelopBG()
{
	telopBG = new Object();

	telopBG->LoadTexture("data/TEXTURE/UI/Telop/telopBG.png");
	telopBG->MakeVertex();

	telopBG->position = POSITION_TELOP_BG;
	telopBG->size = SIZE_TELOP_BG;
	telopBG->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	telopBG->SetColorObject(SET_COLOR_NOT_COLORED);

	percentage = INITIALVALUE_BG_PERCENTAGE;
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
TelopBG::~TelopBG()
{
	SAFE_DELETE(telopBG);
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
	telopBG->Draw();
	SetVertex(percentage);
}

//=============================================================================
// オブジェクトの頂点座標の設定　（テロップ背景専用）
//=============================================================================
void TelopBG::SetVertex(float percentage)
{
	// 頂点座標の設定
	telopBG->vertexWk[0].vtx = D3DXVECTOR3(0, telopBG->position.y -telopBG->size.y*percentage, telopBG->position.z);
	telopBG->vertexWk[1].vtx = D3DXVECTOR3(SCREEN_WIDTH, telopBG->position.y -telopBG->size.y*percentage, telopBG->position.z);
	telopBG->vertexWk[2].vtx = D3DXVECTOR3(0, telopBG->position.y +telopBG->size.y*percentage, telopBG->position.z);
	telopBG->vertexWk[3].vtx = D3DXVECTOR3(SCREEN_WIDTH, telopBG->position.y +telopBG->size.y*percentage, telopBG->position.z);
}

//=============================================================================
// 背景を開く処理
//=============================================================================
void TelopBG::OpenTelopBG(void)
{
	SetEasingValueTelopBGOpen();
	percentage = Easing::EaseValue(telopBG->GetCountObject(DURATION_OPEN_CLOSE), easingStart, easingGoal, InOutCubic);

	if(percentage >= easingGoal)
	{
		telopBGOpenActivated = false;
		percentage = 1.0f;
		telopBG->countFrame = 0;
	}
}

//=============================================================================
// 背景を閉じる処理
//=============================================================================
void TelopBG::CloseTelopBG(void)
{
	SetEasingValueTelopBGClose();
	percentage = Easing::EaseValue(telopBG->GetCountObject(DURATION_OPEN_CLOSE), easingStart, easingGoal, InOutCubic);

	if(percentage <= easingGoal)
	{
		telopBGCloseActivated = false;
		percentage = 0.0f;
		telopBG->countFrame = 0;
	}
}

//=============================================================================
// 背景openイージングセット処理
//=============================================================================
void TelopBG::SetEasingValueTelopBGOpen(void)
{	
	easingStart = INITIALVALUE_BG_PERCENTAGE;
	easingGoal = 1.0f;
}

//=============================================================================
// 背景closeイージングセット処理
//=============================================================================
void TelopBG::SetEasingValueTelopBGClose(void)
{
	easingStart = 1.0f;
	easingGoal = INITIALVALUE_BG_PERCENTAGE;
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