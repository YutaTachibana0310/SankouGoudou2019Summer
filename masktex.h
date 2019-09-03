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

class Object;

class Mask
{
public:
	Mask(float size_x, float size_y, float size_z);
	~Mask();

	void Init(void);

	void Uninit(void);

	void Update(void);

	//�}�X�N�p�e�N�X�`���X�V����
	void FadeOut(void);
	void FadeIn(void);

	//�}�X�N�p�̃e�N�X�`���`��
	void DrawMaskTexSet(void);
	void DrawMaskTexEnd(void);

	void SceneChangeFlag(bool fadeflag, Scene next);

private:
	Object * masktex;
	Scene nextscene;

	//�g��k�����n�܂�t���O
	bool sizechange;
	//�t�F�[�h�C���A�A�E�g�̂ǂ��炩�𔻒肷��t���O
	bool isFadeIn;
	//�t�F�[�h���s��������
	bool active;
	//�V�[���؂�ւ��ׂ̈̃E�F�C�g�^�C��
	int wait;

};

#endif