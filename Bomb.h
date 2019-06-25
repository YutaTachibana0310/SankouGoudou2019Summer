//=============================================================================
//
// ボム(ミサイル)の処理[Bomb.cpp]
// Author : 渡邉良則
//
//=============================================================================
#ifndef _BOMB_H_
#define _BOMB_H_



#define BOMB_SIZE_X
#define BOMB_SIZE_Y
#define BOMB_SIZE_Z



class Player;

class Bomb
{
public:
	bool active = false;

	D3DXVECTOR3 pos;

	int target;
	int cntFrame;
	int reachFrame;
	D3DXVECTOR3 velocity;

	float alpha;
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBomb(void);
void UninitBomb(void);
void UpdateBomb(void);
void DrawBomb(void);

bool SetBomb(void);

#endif