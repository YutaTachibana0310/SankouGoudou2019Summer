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


	//�T�E���h�̍Đ�
	//if (!Sound::GetInstance()->playsound) {
		//�Q�[���J�n�Ɠ����ɍĐ��A�t�F�[�h�C��

	if (CurrentGameScene == GameScene::State::Battle) {
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
		
	//}
	//else {
		//�t�F�[�h�A�E�g�̊J�n
		//Sound::GetInstance()->FadeOut(GAMEBGM, 4.5f, Sound::GetInstance()->changevol, true);
	//}

	//if (GetKeyboardTrigger(DIK_SPACE)) {
	//	//�悭����V���b�gSE�݂����ɍĐ�
	//	Sound::GetInstance()->SetPlaySE(TESTSE, true, Sound::GetInstance()->changevol);
	//	//Sound::GetInstance()->ChangeSEVolume(TESTSE, 1.0f);
	//}
	//if (GetKeyboardTrigger(DIK_O)) {

	//	Sound::GetInstance()->playsound = Sound::GetInstance()->playsound ? false : true;
	//}
	//if (GetKeyboardTrigger(DIK_P)) {
	//	//true�̏ꍇ�Q�[������SE�Đ�
	//	//false�̏ꍇ�̓|�[�Y����SE�Đ�
	//	Sound::GetInstance()->pause = Sound::GetInstance()->pause ? false : true;
	//	Sound::GetInstance()->SetPlaySE(ENTERSE, Sound::GetInstance()->pause, Sound::GetInstance()->changevol);
	//	Sound::GetInstance()->SetPitchSE(ENTERSE, 0);
	//	Sound::GetInstance()->ChangePauseSound(Sound::GetInstance()->pause);
	//	Sound::GetInstance()->changepitch = 0;
	//}

	//if (GetKeyboardTrigger(DIK_L)) {
	//	Sound::GetInstance()->changepitch += 100;
	//	if (Sound::GetInstance()->changepitch > 1200) {
	//		Sound::GetInstance()->changepitch = 1200;
	//	}
	//	//�|�[�Y����SE���点�邩�e�X�g
	//	Sound::GetInstance()->SetPlaySE(ENTERSE, false, Sound::GetInstance()->changevol);
	//	//�|�[�Y���̂݃s�b�`�̕ύX
	//	Sound::GetInstance()->SetPitchSE(ENTERSE, Sound::GetInstance()->changepitch);

	//}

	//if (GetKeyboardTrigger(DIK_K)) {

	//	Sound::GetInstance()->changepitch -= 100;
	//	if (Sound::GetInstance()->changepitch < -1200) {
	//		Sound::GetInstance()->changepitch = -1200;
	//	}
	//	//�|�[�Y����SE���点�邩�e�X�g
	//	Sound::GetInstance()->SetPlaySE(ENTERSE, false, Sound::GetInstance()->changevol);
	//	//�|�[�Y���̂݃s�b�`�̕ύX
	//	Sound::GetInstance()->SetPitchSE(ENTERSE, Sound::GetInstance()->changepitch);
	//}

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