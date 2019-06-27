//=============================================================================
//
// �X�e���V������ [Stencil.cpp]
// Author : �n糗Ǒ�
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
//�e�N�X�`��������
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

//�e�N�X�`���I������
void UninitMask(void)
{
	ReleaseTexture(&masktex);
	ReleaseTexture(&testtitle);
}

//�}�X�N�p�e�N�X�`���X�V����
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

//�}�X�N�p�e�N�X�`���`��
void DrawMaskTEX(void) {

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//�}�X�N����
	clip.setWriteMaskColor(Clip::Stencil::MaskColor_Fill);
	clip.regionBegin(Clip::Stencil::MaskColor_Trans);

	DrawObject(pDevice, masktex);
	SetVertexObject(&masktex);

	clip.regionEnd();

	//�w�i�`��
	clip.setRefMaskColor(Clip::Stencil::MaskColor_Fill);
	clip.drawBegin();

	DrawObject(pDevice, testtitle);
	SetVertexObject(&testtitle);

	clip.drawEnd();

}