//=====================================
//
//�T�E���h�Q�[���V�[������[SoundGameScene.cpp]
//Author:GP12B332 45�@�n糗Ǒ�
//
//=====================================

#include "sound.h"
#include "SoundGameScene.h"
#include "input.h"

/**************************************
�Đ�����
***************************************/
void SoundGameScene::Play() {

	//�T�E���h�̍Đ�
	if (!Sound::GetInstance()->playsound) {
		//�Q�[���J�n�Ɠ����ɍĐ��A�t�F�[�h�C��
		Sound::GetInstance()->SetPlayBGM(GAMEBGM, true, 0.1f);
		Sound::GetInstance()->FadeIn(GAMEBGM, 10.0f, 1.0f, true);
	}
	else {
		//�t�F�[�h�A�E�g�̊J�n
		Sound::GetInstance()->FadeOut(GAMEBGM, 10.0f, 1.0f, true);
	}

	if (GetKeyboardTrigger(DIK_SPACE)) {
		//�悭����V���b�gSE�݂����ɍĐ�
		Sound::GetInstance()->SetPlaySE(TESTSE, true, 1.0f);
		//Sound::GetInstance()->ChangeSEVolume(TESTSE, 1.0f);
	}
	if (GetKeyboardTrigger(DIK_O)) {

		Sound::GetInstance()->playsound = Sound::GetInstance()->playsound ? false : true;
	}
	if (GetKeyboardTrigger(DIK_P)) {
		//true�̏ꍇ�Q�[������SE�Đ�
		//false�̏ꍇ�̓|�[�Y����SE�Đ�
		Sound::GetInstance()->pause = Sound::GetInstance()->pause ? false : true;
		Sound::GetInstance()->SetPlaySE(ENTERSE, Sound::GetInstance()->pause, 1.0f);
		Sound::GetInstance()->SetPitchSE(ENTERSE, 0);
		Sound::GetInstance()->ChangePauseSound(Sound::GetInstance()->pause);
		Sound::GetInstance()->changepitch = 0;
	}

	if (GetKeyboardTrigger(DIK_L)) {
		Sound::GetInstance()->changepitch += 100;
		if (Sound::GetInstance()->changepitch > 1200) {
			Sound::GetInstance()->changepitch = 1200;
		}
		//�|�[�Y����SE���点�邩�e�X�g
		Sound::GetInstance()->SetPlaySE(ENTERSE, false, 1.0f);
		//�|�[�Y���̂݃s�b�`�̕ύX
		Sound::GetInstance()->SetPitchSE(ENTERSE, Sound::GetInstance()->changepitch);

	}

	if (GetKeyboardTrigger(DIK_K)) {

		Sound::GetInstance()->changepitch -= 100;
		if (Sound::GetInstance()->changepitch < -1200) {
			Sound::GetInstance()->changepitch = -1200;
		}
		//�|�[�Y����SE���点�邩�e�X�g
		Sound::GetInstance()->SetPlaySE(ENTERSE, false, 1.0f);
		//�|�[�Y���̂݃s�b�`�̕ύX
		Sound::GetInstance()->SetPitchSE(ENTERSE, Sound::GetInstance()->changepitch);
	}
}

/**************************************
��~����
***************************************/
void SoundGameScene::Stop() {
	Sound::GetInstance()->SetStopSound();
}