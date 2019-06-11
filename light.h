//=============================================================================
//
// ライト処理 [light.h]
// Author : 
//
//=============================================================================
#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "main.h"

#define	NUM_LIGHT		(3)		// ライトの数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitLight(void);
void UninitLight(void);
void UpdateLight(void);

void GetLightData(D3DCOLORVALUE diffuse[], D3DCOLORVALUE ambient[], D3DXVECTOR4 dir[]);
#endif
