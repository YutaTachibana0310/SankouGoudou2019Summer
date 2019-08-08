//=====================================
//
//ボンバーストックエフェクト処理[BomberStockEffect.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "BomberStockEffect.h"
#include "Framework\Easing.h"

/**************************************
マクロ定義
***************************************/
#define BOMBERSTOCKEFFECT_SIZE					(D3DXVECTOR2(40.0f, 40.0f))
#define BOMBERSTOCKEFFECT_TEX_NAME				"data/TEXTURE/Player/BomberStock.png"

#define BOMBERSTOCKEFFECT_ACTIVE_DURATION		(60)
#define BOMBERSTOCKEFFECT_SCALEUP_DURATION		(30)
#define BOMBERSTOCKEFFECT_SCALEDOWN_DURATION	(30)

/**************************************
コンストラクタ
***************************************/
BomberStockEffect::BomberStockEffect()
{
	active = false;

	polygon = new BoardPolygon();
	polygon->SetSize(BOMBERSTOCKEFFECT_SIZE);
	polygon->LoadTexture(BOMBERSTOCKEFFECT_TEX_NAME);
}

/**************************************
デストラクタ
***************************************/
BomberStockEffect::~BomberStockEffect()
{
	SAFE_DELETE(polygon);
}

/**************************************
初期化処理
***************************************/
void BomberStockEffect::Init()
{
	active = true;
	cntFrame = 0;
}

/**************************************
更新処理
***************************************/
void BomberStockEffect::Update()
{
	if (!active)
		return;

	cntFrame++;

	//スケールイージング
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

	//回転イージング
	float t = (float)cntFrame / BOMBERSTOCKEFFECT_ACTIVE_DURATION;
	float rotAngle = Easing::EaseValue(t, 50.0f, 5.0f,EaseType::OutSine);
	transform.Rotate(0.0f, 0.0f, rotAngle);

	//寿命判定
	if (cntFrame == BOMBERSTOCKEFFECT_ACTIVE_DURATION)
		active = false;

}

/**************************************
描画処理
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