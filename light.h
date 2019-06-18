//=============================================================================
//
// ���C�g���� [light.h]
// Author : 
//
//=============================================================================
#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "main.h"

#define	NUM_LIGHT		(3)		// ���C�g�̐�

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitLight(void);
void UninitLight(void);
void UpdateLight(void);

void GetLightData(D3DCOLORVALUE diffuse[], D3DCOLORVALUE ambient[], D3DXVECTOR4 dir[]);
#endif
