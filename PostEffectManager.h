//=====================================
//
//ポストエフェクトマネージャヘッダ[PostEffectManager.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _TEMPLATE_H_
#define _TEMPLATE_H_

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
void InitPostEffectManager(int num);
void UninitPostEffectManager(int num);
void UpdatePostEffectManager(void);
void DrawPostEffectManager(void);

#endif