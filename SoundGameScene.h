//=====================================
//
//�T�E���h�Q�[���V�[���w�b�_[SoundGameScene.h]
//Author:GP12B332 45�@�n糗Ǒ�
//
//=====================================
#ifndef _SOUNDGAMESCENE_H_
#define _SOUNDGAMESCENE_H_

#include "main.h"
#include "SoundStateScene.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class SoundGameScene : public SoundStateScene
{
public:
	void Play();
	void Stop();

	SoundGameScene() {};
	~SoundGameScene() {};
};

#endif