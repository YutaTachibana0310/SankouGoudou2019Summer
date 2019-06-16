//=====================================
//
//スピードブラーコントローラ処理[SpeedBlurController.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "SpeedBlurFilter.h"
#include "SpeedBlurController.h"

/**************************************
マクロ定義
***************************************/
//#define SPEEDBLURCTRL_USE_DEBUG

#ifdef SPEEDBLURCTRL_USE_DEBUG
#include "../debugWindow.h"
#endif // SPEEDBLURCTRL_USE_DEBUG

/**************************************
クラス定義
***************************************/

/**************************************
グローバル変数
***************************************/

/**************************************
描画処理
***************************************/
void SpeedBlurController::Draw()
{
#ifdef SPEEDBLURCTRL_USE_DEBUG
	BeginDebugWindow("SpeedBlur");
	static float startLen = 0.05f;
	static float power = 5.0f;
	DebugSliderFloat("StartLength", &startLen, 0.0f, 1.0f);
	DebugSliderFloat("Power", &power, 0.0f, 150.0f);
	speedBlur->SetStartLength(startLen);
	speedBlur->SetPower(power);
	EndDebugWindow("SpeedBlur");
#endif // SPEEDBLURCTRL_USE_DEBUG

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	LPDIRECT3DSURFACE9 oldSuf;
	pDevice->GetRenderTarget(0, &oldSuf);
	pDevice->SetRenderTarget(0, surface);

	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

	pDevice->SetTexture(0, GetCurrentDrawData());
	speedBlur->DrawEffect();

	pDevice->SetRenderTarget(0, oldSuf);
	SAFE_RELEASE(oldSuf);

	pDevice->SetTexture(0, texture);
	speedBlur->Draw();

	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}

/**************************************
コンストラクタ
***************************************/
SpeedBlurController::SpeedBlurController()
{
	const float InitStartLength = 0.3f;
	const float InitPower = 5.0f;

	speedBlur = new SpeedBlur();
	speedBlur->SetSurfaceSize((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->CreateTexture(SCREEN_WIDTH, SCREEN_HEIGHT, 1, D3DUSAGE_RENDERTARGET, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &texture, 0);
	texture->GetSurfaceLevel(0, &surface);

	speedBlur->SetCenterPos(D3DXVECTOR3(0.0f, 0.0f, 150.0f));
	speedBlur->SetPower(InitPower);
	speedBlur->SetStartLength(InitStartLength);
}

/**************************************
デストラクタ
***************************************/
SpeedBlurController::~SpeedBlurController()
{
	delete speedBlur;
	SAFE_RELEASE(texture);
	SAFE_RELEASE(surface);
}