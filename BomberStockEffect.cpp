//=====================================
//
//�{���o�[�X�g�b�N�G�t�F�N�g����[BomberStockEffect.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "BomberStockEffect.h"
#include "Framework\Easing.h"

/**************************************
�}�N����`
***************************************/
#define BOMBERSTOCKEFFECT_SIZE					(D3DXVECTOR2(40.0f, 40.0f))
#define BOMBERSTOCKEFFECT_TEX_NAME				"data/TEXTURE/Player/BomberStock.png"

#define BOMBERSTOCKEFFECT_ACTIVE_DURATION		(60)
#define BOMBERSTOCKEFFECT_SCALEUP_DURATION		(30)
#define BOMBERSTOCKEFFECT_SCALEDOWN_DURATION	(30)

/**************************************
�R���X�g���N�^
***************************************/
BomberStockEffect::BomberStockEffect()
{
	active = false;

	polygon = new BoardPolygon();
	polygon->SetSize(BOMBERSTOCKEFFECT_SIZE);
	polygon->LoadTexture(BOMBERSTOCKEFFECT_TEX_NAME);
}

/**************************************
�f�X�g���N�^
***************************************/
BomberStockEffect::~BomberStockEffect()
{
	SAFE_DELETE(polygon);
}

/**************************************
����������
***************************************/
void BomberStockEffect::Init()
{
	active = true;
	cntFrame = 0;
}

/**************************************
�X�V����
***************************************/
void BomberStockEffect::Update()
{
	if (!active)
		return;

	cntFrame++;

	//�X�P�[���C�[�W���O
	if (cntFrame < BOMBERSTOCKEFFECT_SCALEUP_DURATION)
	{
		float t = (float)cntFrame / BOMBERSTOCKEFFECT_SCALEUP_DURATION;
		transform.scale = Easing::EaseValue(t, 0.0f, 1.0f, EaseType::OutExpo) * D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	}
	else
	{
		float t = (float)(cntFrame - BOMBERSTOCKEFFECT_SCALEUP_DURATION) / BOMBERSTOCKEFFECT_SCALEDOWN_DURATION;
		transform.scale = Easing::EaseValue(t, 1.0f, 0.0f, EaseType::InCubic) * D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	}

	//��]�C�[�W���O
	float t = (float)cntFrame / BOMBERSTOCKEFFECT_ACTIVE_DURATION;
	float rotAngle = Easing::EaseValue(t, 50.0f, 5.0f,EaseType::OutSine);
	transform.Rotate(0.0f, 0.0f, rotAngle);

	//��������
	if (cntFrame == BOMBERSTOCKEFFECT_ACTIVE_DURATION)
		active = false;

}

/**************************************
�`�揈��
***************************************/
void BomberStockEffect::Draw()
{
	if (!active)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ZENABLE, false);
	pDevice->SetRenderState(D3DRS_LIGHTING, false);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	transform.SetWorld();
	polygon->Draw();

	pDevice->SetRenderState(D3DRS_ZENABLE, true);
	pDevice->SetRenderState(D3DRS_LIGHTING, true);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}