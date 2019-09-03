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

class Object;

class Mask
{
public:
	Mask(float size_x, float size_y, float size_z);
	~Mask();

	void Init(void);

	void Uninit(void);

	void Update(void);

	//マスク用テクスチャ更新処理
	void FadeOut(void);
	void FadeIn(void);

	//マスク用のテクスチャ描画
	void DrawMaskTexSet(void);
	void DrawMaskTexEnd(void);

	void SceneChangeFlag(bool fadeflag, Scene next);

private:
	Object * masktex;
	Scene nextscene;

	//拡大縮小が始まるフラグ
	bool sizechange;
	//フェードイン、アウトのどちらかを判定するフラグ
	bool isFadeIn;
	//フェード実行中か判定
	bool active;
	//シーン切り替えの為のウェイトタイム
	int wait;

};

#endif