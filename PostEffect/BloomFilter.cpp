//=====================================
//
//�u���[���t�B���^�[����[BloomFilter.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "BloomFilter.h"

/**************************************
�}�N����`
***************************************/
#define EFFECTFILE_BLOOMFILTER_PATH		"PostEffect/BloomFilter.fx"
#define PRECOMPILE_BLOOMFILTER_PATH		"data/EFFECT/BloomFilter.cfx"

/**************************************
�N���X��`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
BloomFilter::BloomFilter()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	HRESULT res = D3DXCreateEffectFromFile(pDevice, (LPSTR)PRECOMPILE_BLOOMFILTER_PATH, 0, 0, D3DXSHADER_SKIPVALIDATION, 0, &effect, 0);

	if(res != S_OK)
		D3DXCreateEffectFromFile(pDevice, (LPSTR)EFFECTFILE_BLOOMFILTER_PATH, 0, 0, 0, 0, &effect, 0);

	hThrethold = effect->GetParameterByName(0, "threthold");
	hBloomPower = effect->GetParameterByName(0, "bloomPower");
}

/**************************************
�f�X�g���N�^
***************************************/
BloomFilter::~BloomFilter()
{
	SAFE_RELEASE(effect);
}

/**************************************
�`�揈��
***************************************/
void BloomFilter::DrawEffect(UINT pass)
{
	effect->Begin(0, 0);
	effect->BeginPass(pass);

	ScreenObject::Draw();

	effect->EndPass();
	effect->End();
}

/**************************************
�������l�ݒ菈��
***************************************/
void BloomFilter::SetThrethold(float threthold)
{
	effect->SetFloat(hThrethold, threthold);
	effect->CommitChanges();
}

/**************************************
�Q�C���ݒ菈��
***************************************/
void BloomFilter::SetBloomPower(float power)
{
	effect->SetFloat(hBloomPower, power);
	effect->CommitChanges();
}