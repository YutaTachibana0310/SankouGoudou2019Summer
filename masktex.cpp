//=============================================================================
//
// ステンシル処理 [Stencil.cpp]
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
int counta = 0;
float alpha = 0;
//テクスチャ初期化
HRESULT InitMask(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	LoadTexture(pDevice, MASK_TEXTURE, &masktex);
	InitialTexture(&masktex);
	MakeVertexObject(&masktex);

	masktex.size = D3DXVECTOR3(100, 100, 0.0f);
	masktex.position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT/2, 0.0f);
	masktex.rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	SetColorObject(&masktex, SET_COLOR_NOT_COLORED);


	LoadTexture(pDevice, TEST_TEXTURE, &testtitle);
	InitialTexture(&testtitle);
	MakeVertexObject(&testtitle);

	testtitle.size = D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f);
	testtitle.position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	testtitle.rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	SetColorObject(&testtitle, SET_COLOR_NOT_COLORED);



	return S_OK;
}

//テクスチャ終了処理
void UninitMask(void)
{
	ReleaseTexture(&masktex);
	ReleaseTexture(&testtitle);
}

//マスク用テクスチャ更新処理
void UpdateMask(void) {

	//masktex.position. += 1.0f;
	//if (masktex.size.x == testtitle.size.x) {
	//	sizechange = false;
	//}
	//else if (masktex.size.x == 0.0f) {
	//	sizechange = true;
	//}

	//if (sizechange) {
	//	masktex.size += D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	//}
	//else {
	//	masktex.size -= D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	//}
}

//マスク用テクスチャ描画
void DrawMaskTEX(void) {

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//マスク部分
	clip.setWriteMaskColor(Clip::Stencil::MaskColor_Fill);
	clip.regionBegin(Clip::Stencil::MaskColor_Trans);

	DrawObject(pDevice, masktex);
	SetVertexObject(&masktex);

	clip.regionEnd();

	//背景描画
	clip.setRefMaskColor(Clip::Stencil::MaskColor_Fill);
	clip.drawBegin();

	DrawObject(pDevice, testtitle);
	SetVertexObject(&testtitle);

	clip.drawEnd();

}