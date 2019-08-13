//=====================================
//
//�X�p�C�N�m�C�Y����[SpikeNoise.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "SpikeNoise.h"

/**************************************
�}�N����`
***************************************/
#define EFFECTFILE_SPIKENOISE_PATH		"PostEffect/SpikeNoise.fx"
#define PRECOMPILE_SPIKENOISE_PATH		"data/EFFECT/SpikeNoise.cfx"

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
SpikeNoise::SpikeNoise()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	HRESULT res = D3DXCreateEffectFromFile(pDevice, (LPSTR)PRECOMPILE_SPIKENOISE_PATH, 0, 0, D3DXSHADER_SKIPVALIDATION, 0, &effect, 0);

	if(res != S_OK)
		D3DXCreateEffectFromFile(pDevice, (LPSTR)EFFECTFILE_SPIKENOISE_PATH, 0, 0, 0, 0, &effect, 0);

	hndlLength = effect->GetParameterByName(0, "length");
	hBaseY = effect->GetParameterByName(0, "baseY");
}

/**************************************
�f�X�g���N�^
***************************************/
SpikeNoise::~SpikeNoise()
{
	SAFE_RELEASE(effect);
}

/**************************************
�`�揈��
***************************************/
void SpikeNoise::DrawEffect()
{
	effect->Begin(0, 0);
	effect->BeginPass(0);

	ScreenObject::Draw();

	effect->EndPass();
	effect->End();
}

/**************************************
�c�ݒ����Z�b�g����
***************************************/
void SpikeNoise::SetLength(float length)
{
	effect->SetFloat(hndlLength, length);
	effect->CommitChanges();
}

/**************************************
Y��_�Z�b�g����
***************************************/
void SpikeNoise::SetBaseY(float f)
{
	effect->SetFloat(hBaseY, f);
	effect->CommitChanges();
}