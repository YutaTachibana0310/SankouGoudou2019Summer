//=====================================
//
//�T�E���h�^�C�g���V�[������[SoundTitleScene.cpp]
//Author:GP12B332 45�@�n糗Ǒ�
//
//=====================================

#include "sound.h"
#include "SoundTitleScene.h"
#include "input.h"

/**************************************
�Đ�����
***************************************/
void SoundTitleScene::Play() {
	//�T�E���h�̍Đ�
	if (!Sound::GetInstance()->playsound) {
		//�Q�[���J�n�Ɠ����ɍĐ��A�t�F�[�h�C��
		Sound::GetInstance()->SetPlayBGM(TITLEBGM, true, (Sound::GetInstance()->changevol / 10.0f));
		Sound::GetInstance()->FadeIn(TITLEBGM, 10.0f, Sound::GetInstance()->changevol, true);
	}
	else {
		//�t�F�[�h�A�E�g�̊J�n
		Sound::GetInstance()->FadeOut(TITLEBGM, 4.5f, 1.0f, true);
	}

	if (Sound::GetInstance()->changevol < 1.0f &&
		GetKeyboardTrigger(DIK_UP)) {
		Sound::GetInstance()->changevol += 0.1f;
	}
	else if (Sound::GetInstance()->changevol > 0.0f &&
		GetKeyboardTrigger(DIK_DOWN)) {
		Sound::GetInstance()->changevol -= 0.1f;
	}
	Sound::GetInstance()->ChangeBGMVolume(TITLEBGM, Sound::GetInstance()->changevol);

}

/**************************************
��~����
***************************************/
void SoundTitleScene::Stop() {
	Sound::GetInstance()->SetStopSound();
}