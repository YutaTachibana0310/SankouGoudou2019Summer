//=====================================
//
//�T�E���h�^�C�g���V�[���w�b�_[SoundTitleScene.h]
//Author:GP12B332 45�@�n糗Ǒ�
//
//=====================================
#ifndef _SOUNDTITLESCENE_H_
#define _SOUNDTITLESCENE_H_

#include "main.h"
#include "SoundStateScene.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class SoundTitleScene : public SoundStateScene
{
public:
	void Play();
	void Stop();

	SoundTitleScene() {};
	~SoundTitleScene() {};
};

#endif