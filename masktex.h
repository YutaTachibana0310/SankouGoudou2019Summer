#pragma once
//=====================================
//
//ステンシル処理[Stencil.h]
//Author:GP12B332 45　渡邉良則
//
//=====================================
#ifndef _MASKTEX_H_
#define _MASKTEX_H_

#define	MASK_SIZE (2000.0f)

#define	MASK_TEXTURE			("data/TEXTURE/UI/名称未設定-1.png")	// 読み込むテクスチャファイル名

//テクスチャ初期化
HRESULT InitMask(float size_x, float size_y, float size_z);

//テクスチャの終了処理
void UninitMask(void);

//マスク用テクスチャ更新処理
void MaskFadeOut(void);
void MaskFadeIn(void);

//マスク用のテクスチャ描画
void DrawMaskTexSet(void);
void DrawMaskTexEnd(void);

void SceneChangeFlag(bool fadeflag);
#endif