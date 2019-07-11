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

#define	MASK_TEXTURE			("data/TEXTURE/UI/mask_star.png")	// �ǂݍ��ރe�N�X�`���t�@�C����

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
#endif