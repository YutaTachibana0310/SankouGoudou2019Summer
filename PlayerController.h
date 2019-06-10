#pragma once
//=============================================================================
//
// プレイヤーコントローラー処理 [PlayerController.cpp]
// Author : 渡邉良則
//
//=============================================================================
#ifndef _PLAYERCONTROLLER_H_
#define _PLAYERCONTROLLER_H_

#define JUDG_LEN (5)
#define RESETTIME (120)
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPlayerController(void);
void UpdatePlayerController(HWND hWnd);
void SetPlayerTargetPosition(int *n);

void CheckCW();
void CheckCCW();
bool SetBomb();


//(以下、おーはま追記)

#include "player.h"

//*****************************************************************************
// マクロ定義 (おーはま追記)  一旦追記させてもらいました。次のGMで相談しましょう
//*****************************************************************************
#define INITIAL_ARRAY_NUMBER (8) // 初期化する数字（配列の要素と関係ない値で初期化）

void GetMove_StackCCW(int trailHistoryCCW[MAX_LENGTH]);
void GetMove_StackCW(int trailHistoryCW[MAX_LENGTH]);

#endif
