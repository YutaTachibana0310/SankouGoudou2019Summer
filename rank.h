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

#define	ADRESS_TEXTURE_NUMBER_RANK	"data/TEXTURE/UI/Combo/number_L.png"	// 読み込むテクスチャファイル名
#define	ADRESS_TEXTURE_BG_RANK1	"data/TEXTURE/UI/Result/rank1.png"	// 読み込むテクスチャファイル名
#define	ADRESS_TEXTURE_BG_RANK2	"data/TEXTURE/UI/Result/rank2.png"	// 読み込むテクスチャファイル名
#define	ADRESS_TEXTURE_BG_RANK3	"data/TEXTURE/UI/Result/rank3.png"	// 読み込むテクスチャファイル名
#define	ADRESS_TEXTURE_BG_RANK4	"data/TEXTURE/UI/Result/rank4.png"	// 読み込むテクスチャファイル名
#define	ADRESS_TEXTURE_BG_RANK5	"data/TEXTURE/UI/Result/rank5.png"	// 読み込むテクスチャファイル名
#define	ADRESS_TEXTURE_BG_RANK6	"data/TEXTURE/UI/Result/myrank.png"	// 読み込むテクスチャファイル名

#define MYSCORE (5)
#define RANK_MAX (6)
#define ARRAY_MAX (7)		//最大配列数
#define SIZE_RANK		(D3DXVECTOR3(30.0f,40.0f,0.0f))
#define SIZE_BG_RANK		(D3DXVECTOR3(210.0f,150.0f,0.0f))
#define POSITION_BG_RANK_TOP			(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 6.0f, 0.0))
#define POSITION_BG_RANK_MIDDLE_LEFT	(D3DXVECTOR3(SCREEN_WIDTH / 5.0f, SCREEN_HEIGHT / 5*2.0f, 0.0f))
#define POSITION_BG_RANK_LOWER_LEFT		(D3DXVECTOR3(SCREEN_WIDTH / 5.0f, SCREEN_HEIGHT / 5*4.0f, 0.0f))
#define POSITION_BG_RANK_LOWER_RIGHT	(D3DXVECTOR3(SCREEN_WIDTH / 1.3f, SCREEN_HEIGHT / 5*4.0f, 0.0f))
#define POSITION_BG_RANK_MIDDLE_RIGHT	(D3DXVECTOR3(SCREEN_WIDTH / 1.3f, SCREEN_HEIGHT / 5*2.0f, 0.0f))
#define POSITION_BG_RANK_CENTER			(D3DXVECTOR3(SCREEN_WIDTH / 2.0f ,SCREEN_HEIGHT / 1.8f, 0.0f))

#define POSITION_RANK_TOP			(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 80, SCREEN_HEIGHT / 6.0f + 1000, 0.0f))
#define POSITION_RANK_MIDDLE_LEFT	(D3DXVECTOR3(SCREEN_WIDTH / 5.0f - 1500, SCREEN_HEIGHT / 5*2.0f, 0.0f))
#define POSITION_RANK_LOWER_LEFT	(D3DXVECTOR3(SCREEN_WIDTH / 5.0f - 1500, SCREEN_HEIGHT / 5*4.0f, 0.0f))
#define POSITION_RANK_LOWER_RIGHT	(D3DXVECTOR3(SCREEN_WIDTH / 1.3f + 1500, SCREEN_HEIGHT / 5*4.0f, 0.0f))
#define POSITION_RANK_MIDDLE_RIGHT	(D3DXVECTOR3(SCREEN_WIDTH / 1.3f + 1500, SCREEN_HEIGHT / 5*2.0f, 0.0f))
#define POSITION_RANK_CENTER		(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 80 ,SCREEN_HEIGHT / 1.8f + 10, 0.0f))

typedef struct
{
	int g_scorerank; //数字

} SCORERANK;


HRESULT InitRank(void);

void UninitRank(void);

void UpdateRank(void);

void DrawRank(void);

void RankSort(void);

SCORERANK *GetRank();

#endif