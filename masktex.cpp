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

Clip::Stencil clip;
OBJECT	masktex;
OBJECT	testtitle;

bool sizechange = false;

//テクスチャ初期化
HRESULT InitMask(float size_x, float size_y, float size_z)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	LoadTexture(pDevice, MASK_TEXTURE, &masktex);
	InitialTexture(&masktex);
	MakeVertexObject(&masktex);

	masktex.size = D3DXVECTOR3(size_x, size_y, size_z);
	masktex.position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT/2, 0.0f);
	masktex.rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	SetColorObject(&masktex, SET_COLOR_NOT_COLORED);

	return S_OK;
}

//テクスチャ終了処理
void UninitMask(void)
{
	ReleaseTexture(&masktex);

}

//マスク用テクスチャ更新処理
void MaskFadeOut(void) {


	if (masktex.size.x <= 0) {
		SceneChangeFlag(false);
	}

	if (sizechange) {
		masktex.size -= D3DXVECTOR3(10.0f, 10.0f, 0.0f);

	}

}

void MaskFadeIn(void) {

	if (masktex.size.x >= MASK_SIZE) {
		SceneChangeFlag(false);
	}
	if (sizechange) {
		masktex.size += D3DXVECTOR3(10.0f, 10.0f, 0.0f);

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

	clip.setRefMaskColor(Clip::Stencil::MaskColor_Fill);
	clip.drawBegin();

}

void DrawMaskTexEnd(void) {

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	clip.drawEnd();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);

}

void SceneChangeFlag(bool fadeflag) {

	if (fadeflag) {
		sizechange = true;
	}
	else {
		sizechange = false;
	}
	
}
