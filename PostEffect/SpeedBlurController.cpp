//=====================================
//
//�X�s�[�h�u���[�R���g���[������[SpeedBlurController.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "SpeedBlurFilter.h"
#include "SpeedBlurController.h"
#include "../Framework/Easing.h"

/**************************************
�}�N����`
***************************************/
//#define SPEEDBLURCTRL_USE_DEBUG

#ifdef SPEEDBLURCTRL_USE_DEBUG
#include "../debugWindow.h"
#endif // SPEEDBLURCTRL_USE_DEBUG

/**************************************
�}�N����`
***************************************/
#define SPEEDBLUR_TRANSITION_DURATION		(30)

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�X�V����
***************************************/
void SpeedBlurController::Update()
{
	if (cntPower > 0)
	{
		cntPower--;

		float t = 1.0f - (float)cntPower / SPEEDBLUR_TRANSITION_DURATION;
		float power = Easing::EaseValue(t, startPower, endPower, EaseType::OutCubic);
		speedBlur->SetPower(power);

		if (cntPower == 0)
			startPower = endPower;
	}
}

/**************************************
�`�揈��
***************************************/
void SpeedBlurController::Draw()
{
#ifdef SPEEDBLURCTRL_USE_DEBUG
	BeginDebugWindow("SpeedBlur");
	static float startLen = 0.05f;
	static float power = 0.0f;
	DebugSliderFloat("StartLength", &startLen, 0.0f, 1.0f);
	DebugSliderFloat("Power", &power, 0.0f, 500.0f);
	if (DebugButton("Power+")) power += 20.0f;
	if (DebugButton("Power-")) power -= 20.0f;
	speedBlur->SetStartLength(startLen);
	SetPower(power);
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
�u���[�p���[�Z�b�g����
***************************************/
void SpeedBlurController::SetPower(float power)
{
	endPower = power;

	if (cntPower != 0)
		return;

	cntPower = SPEEDBLUR_TRANSITION_DURATION;
}

/**************************************
�u���[�p���[�Z�b�g����
***************************************/
void SpeedBlurController::AddPower(float power)
{
	endPower += power;

	if (cntPower != 0)
		return;

	cntPower = SPEEDBLUR_TRANSITION_DURATION;
}

/**************************************
�R���X�g���N�^
***************************************/
SpeedBlurController::SpeedBlurController()
{
	const float InitStartLength = 0.35f;
	const float InitPower = 0.0f;

	speedBlur = new SpeedBlur();
	speedBlur->SetSurfaceSize((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->CreateTexture(SCREEN_WIDTH, SCREEN_HEIGHT, 1, D3DUSAGE_RENDERTARGET, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &texture, 0);
	texture->GetSurfaceLevel(0, &surface);

	speedBlur->SetCenterPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	speedBlur->SetPower(InitPower);
	speedBlur->SetStartLength(InitStartLength);

	startPower = endPower = 0.0f;
	cntPower = SPEEDBLUR_TRANSITION_DURATION;
}

/**************************************
�f�X�g���N�^
***************************************/
SpeedBlurController::~SpeedBlurController()
{
	delete speedBlur;
	SAFE_RELEASE(texture);
	SAFE_RELEASE(surface);
}