//=============================================================================
//
// ランキング処理 [rank.h]
// Author : 渡邉良則
//
//=============================================================================
#ifndef _RANK_H
#define _RANK_H

#include "main.h"
#include "UIdrawer.h"

#define	ADRESS_TEXTURE_NUMBER_RANK	"data/TEXTURE/UI/number.png"	// 読み込むテクスチャファイル名
#define RANK_MAX (6)
#define SIZE_RANK		(D3DXVECTOR3(20.0f,30.0f,0.0f))
#define POSITION_RANK_TOP			(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 5, 0.0f))
#define POSITION_RANK_MIDDLE_LEFT	(D3DXVECTOR3(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 5*2, 0.0f))
#define POSITION_RANK_LOWER_LEFT	(D3DXVECTOR3(SCREEN_WIDTH / 3*1.2, SCREEN_HEIGHT / 5*4, 0.0f))
#define POSITION_RANK_LOWER_RIGHT	(D3DXVECTOR3(SCREEN_WIDTH / 3*1.8, SCREEN_HEIGHT / 5*4, 0.0f))
#define POSITION_RANK_MIDDLE_RIGHT	(D3DXVECTOR3(SCREEN_WIDTH / 3*2, SCREEN_HEIGHT / 5*2, 0.0f))


HRESULT InitRank(void);

void UninitRank(void);

void DrawRank(void);

OBJECT *GetRank();

#endif
