//=====================================
//
//�T�E���h�Q�[���V�[������[SoundGameScene.cpp]
//Author:GP12B332 45�@�n糗Ǒ�
//
//=====================================

#include "sound.h"
#include "SoundGameScene.h"
#include "GameScene.h"
#include "input.h"

int CurrentGameScene;
bool BossBGM_active;
/**************************************
�Đ�����
***************************************/
void SoundGameScene::Play() {

	if (CurrentGameScene == GameScene::State::Battle) {
		//�O�̂��߃{�XBGM���~���Q�[��BGM���Đ�
		Sound::GetInstance()->SetStopSound(BOSSBGM);
		Sound::GetInstance()->SetPlayBGM(GAMEBGM, true, Sound::GetInstance()->changevol / 8.0f);
		Sound::GetInstance()->FadeIn(GAMEBGM, 5.0f, Sound::GetInstance()->changevol / 8.0f, true);
	}
	else if (CurrentGameScene == GameScene::State::BossBattle) {

		//�Q�[��BGM�t�F�[�h�A�E�g
		Sound::GetInstance()->FadeOut(GAMEBGM, 5.0f, Sound::GetInstance()->changevol / 8.0f, true);

		//�{�XBGM
		Sound::GetInstance()->SetPlayBGM(BOSSBGM, true, Sound::GetInstance()->changevol / 5.0f);
		Sound::GetInstance()->FadeIn(BOSSBGM, 5.0f, Sound::GetInstance()->changevol / 5.0f, true);

	}
	else if (CurrentGameScene == GameScene::State::End) {

		//�{�XBGM�t�F�[�h�A�E�g
		Sound::GetInstance()->FadeOut(BOSSBGM, 5.0f, Sound::GetInstance()->changevol / 5.0f, true);
	}

}

/**************************************
��~����
***************************************/
void SoundGameScene::Stop() {
	Sound::GetInstance()->SetStopSoundOll();

}

/**************************************
�V�[���擾����
***************************************/
void SoundGameScene::SetScene(int gamescene) {
	CurrentGameScene = gamescene;
}
