//=====================================
//
//�X�s�[�h�u���[�t�B���^�[����[SpeedBlurFilter.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "SpeedBlurFilter.h"

/**************************************
�}�N����`
***************************************/
#define EFEFCTFILE_SPEEDBLUR_PATH		"PostEffect/SpeedBlur.fx"
#define PRECOMPILE_SPEEDBLUR_PATH		"data/EFFECT/SpeedBlur.cfx"

/**************************************
�N���X��`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
SpeedBlur::SpeedBlur()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	HRESULT res =  D3DXCreateEffectFromFile(pDevice, (LPSTR)PRECOMPILE_SPEEDBLUR_PATH, 0, 0, D3DXSHADER_SKIPVALIDATION, 0, &effect, 0);
	
	if(res != S_OK)
		D3DXCreateEffectFromFile(pDevice, (LPSTR)EFEFCTFILE_SPEEDBLUR_PATH, 0, 0, 0, 0, &effect, 0);

	hPower = effect->GetParameterByName(0, "blurPower");
	hCenter = effect->GetParameterByName(0, "centerTexel");
	hTU = effect->GetParameterByName(0, "tU");
	hTV = effect->GetParameterByName(0, "tV");
	hStartLength = effect->GetParameterByName(0, "startLength");
}

/**************************************
�f�X�g���N�^
***************************************/
SpeedBlur::~SpeedBlur()
{
	SAFE_RELEASE(effect);
}

/**************************************
�`�揈��
***************************************/
void SpeedBlur::DrawEffect()
{
	effect->Begin(0, 0);
	effect->BeginPass(0);

	ScreenObject::Draw();

	effect->EndPass();
	effect->End();
}

/**************************************
�p���[�Z�b�g����
***************************************/
void SpeedBlur::SetPower(float power)
{
	effect->SetFloat(hPower, power);
	effect->CommitChanges();
}

/**************************************
�Z���^�[�Z�b�g����
***************************************/
void SpeedBlur::SetCenterPos(D3DXVECTOR3 pos)
{
	D3DXMATRIX view, proj;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DVIEWPORT9 viewport;
	D3DXVECTOR3 center;

	pDevice->GetTransform(D3DTS_VIEW, &view);
	pDevice->GetTransform(D3DTS_PROJECTION, &proj);
	pDevice->GetViewport(&viewport);

	D3DXVec3TransformCoord(&center, &pos, &view);
	D3DXVec3TransformCoord(&center, &center, &proj);
	center.x = (center.x + 1.0f) / 2.0f;
	center.y = (-center.y + 1.0f) / 2.0f;

	effect->SetFloatArray(hCenter, (float*)&center, 2);
	effect->CommitChanges();
}

/**************************************
�e�N�Z���T�C�Y�ݒ菈��
***************************************/
void SpeedBlur::SetSurfaceSize(float width, float height)
{
	float texelU = 1.0f / width;
	float texelV = 1.0f / height;

	effect->SetFloat(hTU, texelU);
	effect->SetFloat(hTV, texelV);
	effect->CommitChanges();
}

/**************************************
�u���[�J�n�����Z�b�g����
***************************************/
void SpeedBlur::SetStartLength(float length)
{
	effect->SetFloat(hStartLength, length);
	effect->CommitChanges();
}