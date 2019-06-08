//=====================================
//
//スコアパーティクルヘッダ[ScoreParticle.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _SCOREPARTICLE_H_
#define _SCOREPARTICLE_H_

#include "main.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/

/**************************************
プロトタイプ宣言
***************************************/
void InitScoreParticle(int num);
void UninitScoreParticle(int num);
void UpdateScoreParticle(void);
void DrawScoreParticle(void);

#endif