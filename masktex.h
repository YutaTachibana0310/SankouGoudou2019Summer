#pragma once
//=====================================
//
//�}�X�N���� [masktex.h]
//Author:GP12B332 45�@�n糗Ǒ�
//
//=====================================
#ifndef _MASKTEX_H_
#define _MASKTEX_H_

#include "Game.h"

#define	MASK_SIZE (2000.0f)

#define POSITION_MASKTEX	(D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0))
#define SIZE_MASKTEX		(D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0.0f))

#define POSITION_MASKBG	(D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,5000.0f))
#define SIZE_MASKBG		(D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0.0f))

#define MAXSIZE_MASKBG  (D3DXVECTOR3(2000.0f,2000.0f,0.0f))

#define ROTATION		(D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(360.0f)))
#define DISAPPER_MASKBG (D3DXVECTOR3(0,0,0))

#define	MASK_TEXTURE			("data/TEXTURE/UI/mask_star.png")	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	MASK_TEXTUREBG			("data/TEXTURE/UI/transition.jpg")	// �ǂݍ��ރe�N�X�`���t�@�C����

//�e�N�X�`��������
HRESULT InitMask(float size_x, float size_y, float size_z);

//�e�N�X�`���̏I������
void UninitMask(void);

void UpdateMask(void);

//�}�X�N�p�e�N�X�`���X�V����
void MaskFadeOut(void);
void MaskFadeIn(void);

//�}�X�N�p�̃e�N�X�`���`��
void DrawMaskTexSet(void);
void DrawMaskTexEnd(void);

void SceneChangeFlag(bool fadeflag,Scene next);

//���[�h��ʕ\��
void DrawTransition(void);
#endif