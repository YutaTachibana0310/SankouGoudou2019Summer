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
#define RESETTIME (120)

#define PLAYER_CENTER		D3DXVECTOR3(0.0f ,-25.0f, 0.0f)
#define PLAYER_TOP			D3DXVECTOR3(0.0f, 25.0f, 150.0f)
#define PLAYER_MIDDLE_LEFT	D3DXVECTOR3(-50.0f, -10.0f, 150.0f)
#define PLAYER_LOWER_LEFT	D3DXVECTOR3(-30.0f, -50.0f, 150.0f)
#define PLAYER_LOWER_RIGHT	D3DXVECTOR3(30.0f, -50.0f, 150.0f)
#define PLAYER_MIDDLE_RIGHT	D3DXVECTOR3(50.0f, -10.0f, 150.0f)

#define PLAYER_MOVE_TIME	(20)
#define PLAYER_RETURN_TIME	(60)

#define MOVESTACK_LENGTH (6)

//プレイヤーの状態列挙子
enum class PlayerState 
{
	Move,
	Wait,
	Return,
};

//前方宣言
class Player;
enum class TrailIndex;
class PlayerBullet;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPlayerController(void);
void UninitPlayerController(void);
void UpdatePlayerController(HWND hWnd);
void DrawPlayerController();
void DrawPlayerBullet();

void CheckCW();
void CheckCCW();
bool SetBomb();

std::vector<PlayerBullet*>* GetPlayerBulletContainer(void);
void ChangeState(Player *player, PlayerState next);
void FirePlayerBullet(TrailIndex start, TrailIndex end);
void FirePlayerBullet(D3DXVECTOR3 *rightPos, D3DXVECTOR3 *leftPos);

//(以下、おーはま追記)
//*****************************************************************************
// マクロ定義 (おーはま追記)  一旦追記させてもらいました。次のGMで相談しましょう
//*****************************************************************************
#define INITIAL_ARRAY_NUMBER (8) // 初期化する数字（配列の要素と関係ない値で初期化）

void GetMove_StackCCW(int trailHistoryCCW[MOVESTACK_LENGTH]);
void GetMove_StackCW(int trailHistoryCW[MOVESTACK_LENGTH]);

#endif
