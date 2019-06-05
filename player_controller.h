#pragma once
//=============================================================================
//
// プレイヤーコントローラー処理 [player_controller.cpp]
// Author : 渡邉良則
//
//=============================================================================
#ifndef _PLAYER_CONTROLLER_H_
#define _PLAYER_CONTROLLER_H_


typedef struct
{

	//判定配列の内容と合っているかの判定
	bool matching;
	bool matching2;

	//一筆書きできた時用のテストフラグ
	bool flag;
	int flag_count;

						
	

}PLAYER_CONTROLLER;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPlayerController(void);
void UpdatePlayerController(HWND hWnd);
void SetPlayerTargetPosition(int *n);
void push(void);

PLAYER_CONTROLLER* GetPlayerController();


#endif
