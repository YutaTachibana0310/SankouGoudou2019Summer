//=====================================
//
//�e���v���[�g�w�b�_[BackGroundField.h]
//Author:GP12B332 28 �������
//
//=====================================
#ifndef _BACKGROUNDFIELD_H_
#define _BACKGROUNDFIELD_H_

#include "main.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/

/**************************************
�v���g�^�C�v�錾
***************************************/
HRESULT InitBackGroundField(void);
void UninitBackGroundField(void);
void UpdateBackGroundField(void);
void DrawBackGroundField(void);
HRESULT MakeVertexBackGroundField(LPDIRECT3DDEVICE9 pDevice);

#endif
