#pragma once
//=====================================
//
//�X�e���V������[Stencil.h]
//Author:GP12B332 45�@�n糗Ǒ�
//
//=====================================
#ifndef _MASKTEX_H_
#define _MASKTEX_H_



#define	MASK_TEXTURE			("data/TEXTURE/UI/�}�X�N�摜.png")	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEST_TEXTURE			("data/TEXTURE/UI/ddon.png")	// �ǂݍ��ރe�N�X�`���t�@�C����

//�e�N�X�`��������
HRESULT InitMask(void);

//�e�N�X�`���̏I������
void UninitMask(void);

//�}�X�N�p�e�N�X�`���X�V����
void UpdateMask(void);

//�}�X�N�p�̃e�N�X�`���`��
void DrawMaskTEX(void);

#endif