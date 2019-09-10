//=====================================
//
//サウンドタイトルシーン処理[SoundTitleScene.cpp]
//Author:GP12B332 45　渡邉良則
//
//=====================================

#include "sound.h"
#include "SoundTitleScene.h"
#include "soundUI.h"
#include "input.h"

/**************************************
再生処理
***************************************/
void SoundTitleScene::Play() {

	Sound::GetInstance()->SetPlayBGM(TITLEBGM, true, (Sound::GetInstance()->changevol / 2.0f));
	Sound::GetInstance()->ChangeBGMVolume(TITLEBGM, Sound::GetInstance()->changevol / 2.0f);


	if (Sound::GetInstance()->changevol < 1.0f &&
		GetKeyboardTrigger(DIK_UP)) {

		Sound::GetInstance()->changevol += 0.2f;

		if (Sound::GetInstance()->changevol > 1.0f) {
			Sound::GetInstance()->changevol = 1.0f;
		}

		Sound::GetInstance()->UIcounta++;
		if (Sound::GetInstance()->UIcounta > SOUNDUI_PARTS_MAX) {
			Sound::GetInstance()->UIcounta = SOUNDUI_PARTS_MAX;
		}

	}
	else if (Sound::GetInstance()->changevol > 0.0f &&
		GetKeyboardTrigger(DIK_DOWN)) {

		Sound::GetInstance()->changevol -= 0.2f;

		if (Sound::GetInstance()->changevol <= 0.0f) {
			Sound::GetInstance()->changevol = 0.0f;
		}

		Sound::GetInstance()->UIcounta--;
		if (Sound::GetInstance()->UIcounta < SOUND_LINE_ONE) {
			Sound::GetInstance()->UIcounta = SOUND_LINE_ONE;
		}

	}


}

/**************************************
停止処理
***************************************/
void SoundTitleScene::Stop() {
	Sound::GetInstance()->SetStopSoundOll();
}