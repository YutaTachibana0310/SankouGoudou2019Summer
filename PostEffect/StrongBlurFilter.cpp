//=====================================
//
//�X�g�����O�u���[�t�B���^����[StrongBlurFilter.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "StrongBlurFilter.h"

/**************************************
�}�N����`
***************************************/
#define EFFECTFILE_STRONGBLUR_PATH		"PostEffect/StrongBlurFilter.fx"
#define PRECOMPILE_STRONGBLUR_PATH	"data/EFFECT/StrongBlurFilter.cfx"

#define STRONGBLUR_ARRAY_SIZE		(9)

/**************************************
�N���X��`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
StrongBlurFilter::StrongBlurFilter()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	HRESULT res = D3DXCreateEffectFromFile(pDevice, (LPSTR)PRECOMPILE_STRONGBLUR_PATH, 0, 0, D3DXSHADER_SKIPVALIDATION, 0, &effect, 0);

	if(res != S_OK)
		D3DXCreateEffectFromFile(pDevice, (LPSTR)EFFECTFILE_STRONGBLUR_PATH, 0, 0, 0, 0, &effect, 0);

	hTexelU = effect->GetParameterByName(0, "texelU");
	hTexelV = effect->GetParameterByName(0, "texelV");
	effect->SetTechnique("tech");
}

/**************************************
�f�X�g���N�^
***************************************/
StrongBlurFilter::~StrongBlurFilter()
{
	SAFE_RELEASE(effect);
}

/**************************************
�`�揈��
***************************************/
void StrongBlurFilter::DrawEffect(UINT pass)
{
	effect->Begin(0, 0);
	effect->BeginPass(pass);

	ScreenObject::Draw();

	effect->EndPass();
	effect->End();
}

/**************************************
�T�[�t�F�C�X�T�C�Y�ݒ菈��
***************************************/
void StrongBlurFilter::SetSurfaceSize(float width, float height)
{
	float u[STRONGBLUR_ARRAY_SIZE], v[STRONGBLUR_ARRAY_SIZE];
	for (int i = 0; i < STRONGBLUR_ARRAY_SIZE; i++)
	{
		u[i] = 1.0f / width * (i + 1);
		v[i] = 1.0f / height * (i + 1);
	}

	effect->SetFloatArray(hTexelU, u, STRONGBLUR_ARRAY_SIZE);
	effect->SetFloatArray(hTexelV, v, STRONGBLUR_ARRAY_SIZE);
	effect->CommitChanges();

	ScreenObject::Resize(width, height);
}