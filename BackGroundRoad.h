//=====================================
//
//テンプレートヘッダ[BackGroundRoad.h]
//Author:GP12B332 28 中西一穂
//
//=====================================
#ifndef _BACKGROUNDROAD_H_
#define _BACKGROUNDROAD_H_

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
HRESULT InitBackGroundRoad(void);
void UninitBackGroundRoad(void);
void UpdateBackGroundRoad(void);
void DrawBackGroundRoad(void);
HRESULT MakeVertexBackGroundRoad(LPDIRECT3DDEVICE9 pDevice);

#endif