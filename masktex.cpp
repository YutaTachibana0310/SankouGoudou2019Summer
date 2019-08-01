//=============================================================================
//
// マスク処理 [masktex.cpp]
// Author : 渡邉良則
//
//=============================================================================
#include "main.h"
#include "masktex.h"
#include "UIdrawer.h"
#include "Stencil.h"
#include "Game.h"

Clip::Stencil clip;
OBJECT	masktex;
OBJECT	maskBG;

//拡大縮小が始まるフラグ
bool sizechange;
//フェードイン、アウトのどちらかを判定するフラグ
bool isFadeIn;
//フェード実行中か判定
bool active;
//シーン切り替えの為のウェイトタイム
int wait;

Scene nextscene;

//テクスチャ初期化
HRESULT InitMask(float size_x, float size_y, float size_z)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	LoadTexture(pDevice, MASK_TEXTURE, &masktex);
	InitialTexture(&masktex);
	MakeVertexObject(&masktex);

	masktex.size = D3DXVECTOR3(size_x, size_y, size_z);
	masktex.position = SIZE_MASKBG;
	masktex.rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	SetColorObject(&masktex, SET_COLOR_NOT_COLORED);

	active = false;
	sizechange = false;
	isFadeIn = false;
	wait = 0;

	//ステンシル値が0の時に表示する画像
	LoadTexture(pDevice, MASK_TEXTUREBG, &maskBG);
	InitialTexture(&maskBG);
	MakeVertexObject(&maskBG);
	maskBG.size = SIZE_MASKBG;
	maskBG.position = POSITION_MASKBG;
	maskBG.rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	SetColorObject(&maskBG, SET_COLOR_NOT_COLORED);

	return S_OK;
}

//テクスチャ終了処理
void UninitMask(void)
{
	ReleaseTexture(&masktex);
	ReleaseTexture(&maskBG);

}

void UpdateMask(void) {

	if (active) {
		//isFadeInがtrueの場合にフェードイン
		if (isFadeIn) {
			MaskFadeIn();
		}
		else {
			MaskFadeOut();
		}
	}

}

//マスク用テクスチャ更新処理
void MaskFadeOut(void) {

	if (sizechange) {
		masktex.size -= D3DXVECTOR3(20.0f, 20.0f, 0.0f);

	}
	//サイズ小さくなるにつれ画面が黒くなる
	if (masktex.size.x <= 0) {
		masktex.size = D3DXVECTOR3(0,0,0);
		SceneChangeFlag(true, nextscene);

		//サイズ0以下でシーン切り替え
		wait++;

		if (wait > 60) {

			ChangeScene(nextscene);
			isFadeIn = true;
			//active = false;
			wait = 0;

		}

	}

}

void MaskFadeIn(void) {

	if (sizechange) {
		masktex.size += D3DXVECTOR3(20.0f, 20.0f, 0.0f);

	}

	//サイズが大きくなるにつれゲーム画面表示
	if (masktex.size.x >= MASK_SIZE) {

		SceneChangeFlag(false,nextscene);
		active = false;
	}


	

}

//マスク用テクスチャ描画
void DrawMaskTexSet(void) {

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//マスク部分
	clip.setWriteMaskColor(Clip::Stencil::MaskColor_Trans);
	
	clip.regionBegin(Clip::Stencil::MaskColor_Fill);

	DrawObject(pDevice, masktex);
	SetVertexObject(&masktex);

	clip.regionEnd();

	DrawTransition();

	//
	clip.setRefMaskColor(Clip::Stencil::MaskColor_Fill);

	clip.drawBegin();



}

void DrawMaskTexEnd(void) {

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	clip.drawEnd();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);


}

void SceneChangeFlag(bool fadeflag,Scene next) {

	if (fadeflag) {
		sizechange = true;
		nextscene = next;
		active = true;
		isFadeIn = false;
	}
	else {
		sizechange = false;
		active = false;
	}
	
}

void DrawTransition(void) {

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	DrawObject(pDevice, maskBG);
	SetVertexObject(&maskBG);
}

