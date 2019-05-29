//=====================================
//
//ブラーフィルター処理[BlurFilter.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "BlurFilter.h"

/**************************************
マクロ定義
***************************************/
#define EFFECTFILE_BLUR_PATH	"PostEffect/BlurFilter.fx"
#define BLURFILTER_ARRAY_SIZE	(5)

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/

/**************************************
コンストラクタ
***************************************/
BlurFilter::BlurFilter()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXCreateEffectFromFile(pDevice, (LPSTR)EFFECTFILE_BLUR_PATH, 0, 0, 0, 0, &effect, 0);
	texelU = effect->GetParameterByName(0, "texelU");
	texelV = effect->GetParameterByName(0, "texelV");
	effect->SetTechnique("tech");
}

/**************************************
デストラクタ
***************************************/
BlurFilter::~BlurFilter()
{
	SAFE_RELEASE(effect);
}

/**************************************
描画処理
***************************************/
void BlurFilter::DrawEffect(UINT pass)
{
	effect->Begin(0, 0);
	effect->BeginPass(pass);

	ScreenObject::Draw();

	effect->EndPass();
	effect->End();
}

/**************************************
サーフェイスサイズセット処理
***************************************/
void BlurFilter::SetSurfaceSize(float width, float height)
{
	float u[BLURFILTER_ARRAY_SIZE], v[BLURFILTER_ARRAY_SIZE];
	for (int i = 0; i < BLURFILTER_ARRAY_SIZE; i++)
	{
		u[i] = 1.0f / width * (i + 1);
		v[i] = 1.0f / height * (i + 1);
	}

	effect->SetFloatArray(texelU, u, BLURFILTER_ARRAY_SIZE);
	effect->SetFloatArray(texelV, v, BLURFILTER_ARRAY_SIZE);
	effect->CommitChanges();

	ScreenObject::Resize(width, height);
}