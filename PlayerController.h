#pragma once
//=============================================================================
//
// プレイヤーコントローラー処理 [PlayerController.cpp]
// Author : 渡邉良則
//
//=============================================================================
#ifndef _PLAYERCONTROLLER_H_
#define _PLAYERCONTROLLER_H_

#include <vector>

#define JUDG_LEN (5)

#define PLAYER_CENTER		D3DXVECTOR3(0.0f ,-25.0f, 0.0f)

#define MOVESTACK_LENGTH (6)

class PlayerObserver;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void GetPlayerMoveHistory(std::vector<int> *pOut);		//移動履歴取得処理
void SetPlayerObserverAdr(PlayerObserver *ptr);
#endif
