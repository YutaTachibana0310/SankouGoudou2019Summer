//=====================================
//
//サウンドタイトルシーン処理[SoundTitleScene.cpp]
//Author:GP12B332 45　渡邉良則
//
//=====================================

#include "sound.h"
#include "SoundTitleScene.h"
#include "input.h"

/**************************************
再生処理
***************************************/
void SoundTitleScene::Play() {
	//サウンドの再生
	if (!Sound::GetInstance()->playsound) {
		//ゲーム開始と同時に再生、フェードイン
		Sound::GetInstance()->SetPlayBGM(TITLEBGM, true, (Sound::GetInstance()->changevol / 10.0f));
		Sound::GetInstance()->FadeIn(TITLEBGM, 10.0f, Sound::GetInstance()->changevol, true);
	}
	else {
		//フェードアウトの開始
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
停止処理
***************************************/
void SoundTitleScene::Stop() {
	Sound::GetInstance()->SetStopSound();
}