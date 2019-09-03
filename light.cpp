//=============================================================================
//
// ���C�g���� [light.cpp]
// Author : GP12B332 21 ���ԗY��
//
//=============================================================================
#include "light.h"
#include "debugWindow.h"
#include <stdio.h>

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define LIGHT_SETTINGS_PATH		"data/SETTINGS/light.ini"	//�ݒ�t�@�C���̃p�X

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
bool SaveLightSettings(void);		//���C�g�̐ݒ�ۑ�����
bool LoadLightSettings(void);		//���C�g�̐ݒ�ǂݍ��ݏ���

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
D3DLIGHT9 g_aLight[NUM_LIGHT];		// ���C�g�̃��[�N

D3DXCOLOR lightDiffuse[NUM_LIGHT];

//=============================================================================
// ���C�g�̏���������
//=============================================================================
HRESULT InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXVECTOR3 vecDir;

	bool loadSuccess = LoadLightSettings();

	if (!loadSuccess)
	{
		// D3DLIGHT9�\���̂�0�ŃN���A����
		ZeroMemory(&g_aLight[0], sizeof(D3DLIGHT9));
		// D3DLIGHT9�\���̂�0�ŃN���A����
		ZeroMemory(&g_aLight[2], sizeof(D3DLIGHT9));
		// D3DLIGHT9�\���̂�0�ŃN���A����
		ZeroMemory(&g_aLight[1], sizeof(D3DLIGHT9));

		// ���C�g0�̐ݒ�
		g_aLight[0].Type = D3DLIGHT_DIRECTIONAL;
		g_aLight[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aLight[0].Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aLight[0].Ambient = D3DXCOLOR(0.1f, 0.1f, 0.5f, 1.0f);
		vecDir = D3DXVECTOR3(0.80f, -1.0f, 0.80f);
		D3DXVec3Normalize((D3DXVECTOR3*)&g_aLight[0].Direction, &vecDir);

		// ���C�g1�̐ݒ�
		g_aLight[1].Type = D3DLIGHT_DIRECTIONAL;
		g_aLight[1].Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
		g_aLight[1].Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
		g_aLight[1].Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vecDir = D3DXVECTOR3(-0.0f, 1.00f, -0.50f);
		D3DXVec3Normalize((D3DXVECTOR3*)&g_aLight[1].Direction, &vecDir);

		// ���C�g2�̐ݒ�
		g_aLight[2].Type = D3DLIGHT_DIRECTIONAL;
		g_aLight[2].Diffuse = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
		g_aLight[2].Ambient = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
		g_aLight[2].Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vecDir = D3DXVECTOR3(-0.40f, -0.5f, 0.80f);
		D3DXVec3Normalize((D3DXVECTOR3*)&g_aLight[2].Direction, &vecDir);
	}

	// ���C�g�������_�����O�p�C�v���C���ɐݒ�
	pDevice->SetLight(0, &g_aLight[0]);
	pDevice->LightEnable(0, TRUE);

	// ���C�g�������_�����O�p�C�v���C���ɐݒ�
	pDevice->SetLight(1, &g_aLight[1]);
	pDevice->LightEnable(1, TRUE);

	// ���C�g�������_�����O�p�C�v���C���ɐݒ�
	pDevice->SetLight(2, &g_aLight[2]);
	pDevice->LightEnable(2, TRUE);

	// ���C�e�B���O���[�h
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	return S_OK;
}

//=============================================================================
// ���C�g�̏I������
//=============================================================================
void UninitLight(void)
{

}

//=============================================================================
// ���C�g�̍X�V����
//=============================================================================
void UpdateLight(void)
{

}

//=============================================================================
// ���C�g���擾����
//=============================================================================
void GetLightData(D3DCOLORVALUE diffuse[], D3DCOLORVALUE ambient[], D3DXVECTOR4 dir[])
{
	for (int i = 0; i < NUM_LIGHT; i++)
	{
		diffuse[i] = g_aLight[i].Diffuse;
		ambient[i] = g_aLight[i].Ambient;
		dir[i] = D3DXVECTOR4(g_aLight[i].Direction, 1.0f);
	}
}

//=============================================================================
// ���C�g�̐ݒ�ǂݍ��ݏ���
//=============================================================================
bool LoadLightSettings(void)
{
	FILE *fp = fopen(LIGHT_SETTINGS_PATH, "rb");

	if (fp == NULL)
		return false;

	fread(g_aLight, sizeof(D3DLIGHT9), NUM_LIGHT, fp);

	fclose(fp);
	return true;
}

//=============================================================================
// ���C�g�̐ݒ�ۑ�����
//=============================================================================
bool SaveLightSettings(void)
{
	FILE *fp = fopen(LIGHT_SETTINGS_PATH, "wb");

	if (fp == NULL)
		return false;

	fwrite(g_aLight, sizeof(D3DLIGHT9), NUM_LIGHT, fp);
	fclose(fp);
	return true;
}