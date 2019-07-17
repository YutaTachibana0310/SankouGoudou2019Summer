//=============================================================================
//
// バトルスタートテロップ処理 [battleStartTelop.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "telopBG.h"
#include "Framework/Easing.h"
#include "battleStartTelop.h"
#include "UIdrawer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SIZE_BATTLE_START_TELOP				(D3DXVECTOR3(SCREEN_WIDTH/4,50.0f,0.0f))
#define INIT_POSITION_BATTLE_START_TELOP	(D3DXVECTOR3(SCREEN_WIDTH*1.5,SCREEN_HEIGHT/10*8,0.0f))
#define DURATION_IN_OUT (60.0f)
#define DURATION_STOP	(60.0f)
#define EASING_STOP_POSION_X (SCREEN_CENTER_X)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InBattleStartTelop(void);
void StopBattleStartTelop(void);
void OutBattleStartTelop(void);
void SetEasingValueBattleStartTelopIn(void);
void SetEasingValueBattleStartTelopStop(void);
void SetEasingValueBattleStartTelopOut(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
OBJECT	battleStartTelop;
Easing<float> eBattleStartTelop;
bool 	battleStartTelopInActivated = false;
bool 	battleStartTelopStopActivated = false;
bool 	battleStartTelopOutActivated = false;
bool	animFinished = false;
int		currentSeq = 0;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBattleStartTelop(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	LoadTexture(pDevice, ADRESS_TEXTURE_BATTLE_START_TELOP, &battleStartTelop);
	InitialTexture(&battleStartTelop);
	MakeVertexObject(&battleStartTelop);

	battleStartTelop.position = INIT_POSITION_BATTLE_START_TELOP;
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
	if (GetKeyboardTrigger(DIK_1))
	{
		//テロップ背景オープン
		AvctivateTelopBGOpen();

		battleStartTelopInActivated = true;
	}
	if (GetKeyboardTrigger(DIK_2))
	{
		battleStartTelopOutActivated = true;

		//テロップ背景クローズ
		AvctivateTelopBGClose();

	}
	if (GetKeyboardTrigger(DIK_3))
	{
		SetBattleStartTelop();
	}

	if (battleStartTelopInActivated)
	{
		InBattleStartTelop();
	}
	if (battleStartTelopStopActivated && battleStartTelopInActivated == false)
	{
		StopBattleStartTelop();
	}
	if (battleStartTelopOutActivated && battleStartTelopStopActivated == false)
	{
		OutBattleStartTelop();
	}
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

//=============================================================================
// バトルスタートテロップ挿入処理
//=============================================================================
void InBattleStartTelop(void)
{
	animFinished = false;

	SetEasingValueBattleStartTelopIn();
	battleStartTelop.position.x = eBattleStartTelop.GetEasingValue(GetCountObject(&battleStartTelop, DURATION_IN_OUT), &battleStartTelop.easingStart, &battleStartTelop.easingGoal, InOutCubic);

	if (battleStartTelop.position.x <= battleStartTelop.easingGoal)
	{
		battleStartTelopInActivated = false;
		battleStartTelop.position.x = EASING_STOP_POSION_X;
		battleStartTelop.countFrame = 0;
	}
}

//=============================================================================
// バトルスタートテロップ停止処理
//=============================================================================
void StopBattleStartTelop(void)
{
	SetEasingValueBattleStartTelopStop();
	battleStartTelop.position.x = eBattleStartTelop.GetEasingValue(GetCountObject(&battleStartTelop, DURATION_STOP), &battleStartTelop.easingStart, &battleStartTelop.easingGoal, InOutCubic);

	if (GetCountObject(&battleStartTelop, DURATION_STOP) >= DURATION_STOP/60)
	{
		battleStartTelopStopActivated = false;
		battleStartTelop.position.x = EASING_STOP_POSION_X;
		battleStartTelop.countFrame = 0;
	}
}

//=============================================================================
// バトルスタートテロップ抜去処理
//=============================================================================
void OutBattleStartTelop(void)
{
	SetEasingValueBattleStartTelopOut();
	battleStartTelop.position.x = eBattleStartTelop.GetEasingValue(GetCountObject(&battleStartTelop, DURATION_IN_OUT), &battleStartTelop.easingStart, &battleStartTelop.easingGoal, InOutCubic);

	if (battleStartTelop.position.x <= battleStartTelop.easingGoal)
	{
		animFinished = true;

		battleStartTelopOutActivated = false;
		battleStartTelop.position.x = -INIT_POSITION_BATTLE_START_TELOP.x;
		battleStartTelop.countFrame = 0;
	}
}

//=============================================================================
// バトルスタートテロップ挿入イージングセット処理
//=============================================================================
void SetEasingValueBattleStartTelopIn(void)
{
	battleStartTelop.easingStart = INIT_POSITION_BATTLE_START_TELOP.x;
	battleStartTelop.easingGoal = EASING_STOP_POSION_X;
}

//=============================================================================
// バトルスタートテロップ停止イージングセット処理
//=============================================================================
void SetEasingValueBattleStartTelopStop(void)
{
	battleStartTelop.easingStart = EASING_STOP_POSION_X;
	battleStartTelop.easingGoal = EASING_STOP_POSION_X;
}

//=============================================================================
// バトルスタートテロップ抜去イージングセット処理
//=============================================================================
void SetEasingValueBattleStartTelopOut(void)
{
	battleStartTelop.easingStart = EASING_STOP_POSION_X;
	battleStartTelop.easingGoal = -INIT_POSITION_BATTLE_START_TELOP.x;
}

//=============================================================================
// バトルスタートテロップセット処理
//=============================================================================
void SetBattleStartTelop(void)
{
	//テロップ背景オープン
	AvctivateTelopBGOpen();

	battleStartTelopInActivated = true;
	battleStartTelopStopActivated = true;
	battleStartTelopOutActivated = true;

	//テロップ背景クローズ
	AvctivateTelopBGClose();
}

bool TelopTextAnimFinished(void)
{
	return animFinished;
}
