#pragma once
//=====================================
//
//ステンシル処理[Stencil.h]
//Author:GP12B332 45　渡邉良則
//
//=====================================
#ifndef _MASKTEX_H_
#define _MASKTEX_H_



#define	MASK_TEXTURE			("data/TEXTURE/UI/マスク画像.png")	// 読み込むテクスチャファイル名
#define	TEST_TEXTURE			("data/TEXTURE/UI/ddon.png")	// 読み込むテクスチャファイル名

//テクスチャ初期化
HRESULT InitMask(void);

//テクスチャの終了処理
void UninitMask(void);

//マスク用テクスチャ更新処理
void UpdateMask(void);

//マスク用のテクスチャ描画
void DrawMaskTEX(void);

#endif