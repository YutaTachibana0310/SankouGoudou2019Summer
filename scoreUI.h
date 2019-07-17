//=============================================================================
//
// スコア処理 [score.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	ADRESS_TEXTURE_SCORE		"data/TEXTURE/UI/number.png"	// 読み込むテクスチャファイル名

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	INTERVAL_NUMBER	(40.0f)				// スコア数字の表示間隔
#define	INTERVAL_RANKING_NUMBER	(80.0f)		// スコア数字の表示間隔（ランキング用）
#define	INTERVAL_NUMBER_TEXTURE	(0.097f)	// テクスチャテクスチャ内のスコア数字の表示間隔
#define	PLACE_MAX		(4)					// スコアの桁数
#define BASE_NUMBER		(10)				// 進数
#define VOLUME_ZOOM		(30.0f)
#define SIZE_SCORE		(D3DXVECTOR3(20.0f,30.0f,0.0f))
#define POSITION_SCORE	(D3DXVECTOR3(SCREEN_WIDTH / 10 * 8.8f, SCREEN_HEIGHT / 10 * 8, 0.0f))

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitScore	(void);
void	UninitScore	(void);
void	UpdateScore	(void);
void	DrawScore	(void);
void	AddScore	(int value);
int SetScore();

#endif
