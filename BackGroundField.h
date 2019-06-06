//=====================================
//
//テンプレートヘッダ[BackGroundField.h]
//Author:GP12B332 28 中西一穂
//
//=====================================
#ifndef _BACKGROUNDFIELD_H_
#define _BACKGROUNDFIELD_H_

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
HRESULT InitBackGroundField(void);
void UninitBackGroundField(void);
void UpdateBackGroundField(void);
void DrawBackGroundField(void);
HRESULT MakeVertexBackGroundField(LPDIRECT3DDEVICE9 pDevice);

#endif
