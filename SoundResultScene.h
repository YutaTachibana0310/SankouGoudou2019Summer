//=====================================
//
//�T�E���h���U���g�V�[���w�b�_[SoundResultScene.h]
//Author:GP12B332 45�@�n糗Ǒ�
//
//=====================================
#ifndef _SOUNDRESULTSCENE_H_
#define _SOUNDRESULTSCENE_H_

#include "main.h"
#include "SoundStateScene.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class SoundResultScene : public SoundStateScene
{
public:
	void Play();
	void Stop();

	SoundResultScene() {};
	~SoundResultScene() {};
};

#endif
