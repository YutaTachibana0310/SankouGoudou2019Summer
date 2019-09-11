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

/**************************************
�Đ�����
***************************************/
void SoundGameScene::Play() {

	switch (CurrentGameScene)
	{
	case GameScene::Start:
		//�O�̂��߃{�XBGM���~���Q�[��BGM���Đ�
		Sound::GetInstance()->SetStopSound(BOSSBGM);
		Sound::GetInstance()->SetPlayBGM(GAMEBGM, true, Sound::GetInstance()->changevol / 7.0f);
		Sound::GetInstance()->FadeIn(GAMEBGM, 3.0f, Sound::GetInstance()->changevol / 7.0f, true);
		break;

	case GameScene::Battle:
		//Sound::GetInstance()->SetStopSound(GAMEBGM);
		break;

	case GameScene::BossBattle:

		//�Q�[��BGM�t�F�[�h�A�E�g
		Sound::GetInstance()->FadeOut(GAMEBGM, 5.0f, Sound::GetInstance()->changevol / 8.0f, true);

		//�{�XBGM
		Sound::GetInstance()->SetPlayBGM(BOSSBGM, true, Sound::GetInstance()->changevol / 5.0f);
		Sound::GetInstance()->FadeIn(BOSSBGM, 5.0f, Sound::GetInstance()->changevol / 5.0f, true);
		break;

	case GameScene::End:

		//�{�XBGM�t�F�[�h�A�E�g
		Sound::GetInstance()->FadeOut(BOSSBGM, 5.0f, Sound::GetInstance()->changevol / 5.0f, true);
		break;

	case GameScene::Failed:

		//�Q�[���A�{�XBGM�t�F�[�h�A�E�g
		Sound::GetInstance()->FadeOut(GAMEBGM, 5.0f, Sound::GetInstance()->changevol / 8.0f, true);
		Sound::GetInstance()->FadeOut(BOSSBGM, 5.0f, Sound::GetInstance()->changevol / 5.0f, true);
		break;


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