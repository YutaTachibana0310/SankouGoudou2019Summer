//=====================================
//
//�T�E���h�X�e�[�g�V�[���w�b�_[SoundStateScene.h]
//Author:GP12B332 45�@�n糗Ǒ�
//
//=====================================
#ifndef _SOUNDSTATESCENE_H_
#define _SOUNDSTATESCENE_H_

#include "main.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class SoundStateScene
{
public:
	virtual void Play() = 0;
	virtual void Stop() = 0;


	SoundStateScene() {};
	virtual ~SoundStateScene() {};
};

#endif
