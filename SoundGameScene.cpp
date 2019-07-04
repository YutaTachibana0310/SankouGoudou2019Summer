//=====================================
//
//サウンドゲームシーン処理[SoundGameScene.cpp]
//Author:GP12B332 45　渡邉良則
//
//=====================================

#include "sound.h"
#include "SoundGameScene.h"
#include "input.h"

/**************************************
再生処理
***************************************/
void SoundGameScene::Play() {

	//サウンドの再生
	if (!Sound::GetInstance()->playsound) {
		//ゲーム開始と同時に再生、フェードイン
		Sound::GetInstance()->SetPlayBGM(GAMEBGM, true, 0.1f);
		Sound::GetInstance()->FadeIn(GAMEBGM, 10.0f, 1.0f, true);
	}
	else {
		//フェードアウトの開始
		Sound::GetInstance()->FadeOut(GAMEBGM, 10.0f, 1.0f, true);
	}

	if (GetKeyboardTrigger(DIK_SPACE)) {
		//よくあるショットSEみたいに再生
		Sound::GetInstance()->SetPlaySE(TESTSE, true, 1.0f);
		//Sound::GetInstance()->ChangeSEVolume(TESTSE, 1.0f);
	}
	if (GetKeyboardTrigger(DIK_O)) {

		Sound::GetInstance()->playsound = Sound::GetInstance()->playsound ? false : true;
	}
	if (GetKeyboardTrigger(DIK_P)) {
		//trueの場合ゲーム中にSE再生
		//falseの場合はポーズ中にSE再生
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
		//ポーズ中にSEが鳴らせるかテスト
		Sound::GetInstance()->SetPlaySE(ENTERSE, false, 1.0f);
		//ポーズ中のみピッチの変更
		Sound::GetInstance()->SetPitchSE(ENTERSE, Sound::GetInstance()->changepitch);

	}

	if (GetKeyboardTrigger(DIK_K)) {

		Sound::GetInstance()->changepitch -= 100;
		if (Sound::GetInstance()->changepitch < -1200) {
			Sound::GetInstance()->changepitch = -1200;
		}
		//ポーズ中にSEが鳴らせるかテスト
		Sound::GetInstance()->SetPlaySE(ENTERSE, false, 1.0f);
		//ポーズ中のみピッチの変更
		Sound::GetInstance()->SetPitchSE(ENTERSE, Sound::GetInstance()->changepitch);
	}
}

/**************************************
停止処理
***************************************/
void SoundGameScene::Stop() {
	Sound::GetInstance()->SetStopSound();
}