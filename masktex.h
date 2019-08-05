#pragma once
//=====================================
//
//マスク処理 [masktex.h]
//Author:GP12B332 45　渡邉良則
//
//=====================================
#ifndef _MASKTEX_H_
#define _MASKTEX_H_

#include "Game.h"

#define	MASK_SIZE (2000.0f)

#define POSITION_MASKTEX	(D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0))
#define SIZE_MASKTEX		(D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0.0f))

#define POSITION_MASKBG	(D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,5000.0f))
#define SIZE_MASKBG		(D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0.0f))

#define MAXSIZE_MASKBG  (D3DXVECTOR3(2000.0f,2000.0f,0.0f))

#define ROTATION		(D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(360.0f)))
#define DISAPPER_MASKBG (D3DXVECTOR3(0,0,0))

#define	MASK_TEXTURE			("data/TEXTURE/UI/mask_star.png")	// 読み込むテクスチャファイル名
#define	MASK_TEXTUREBG			("data/TEXTURE/UI/transition.jpg")	// 読み込むテクスチャファイル名

//テクスチャ初期化
HRESULT InitMask(float size_x, float size_y, float size_z);

//テクスチャの終了処理
void UninitMask(void);

void UpdateMask(void);

//マスク用テクスチャ更新処理
void MaskFadeOut(void);
void MaskFadeIn(void);

//マスク用のテクスチャ描画
void DrawMaskTexSet(void);
void DrawMaskTexEnd(void);

void SceneChangeFlag(bool fadeflag,Scene next);

//ロード画面表示
void DrawTransition(void);
#endif