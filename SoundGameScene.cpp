//=====================================
//
//サウンドゲームシーン処理[SoundGameScene.cpp]
//Author:GP12B332 45　渡邉良則
//
//=====================================

#include "sound.h"
#include "SoundGameScene.h"
#include "GameScene.h"
#include "input.h"

int CurrentGameScene;
bool BossBGM_active;
/**************************************
再生処理
***************************************/
void SoundGameScene::Play() {

	if (CurrentGameScene == GameScene::State::Battle) {
		//念のためボスBGMを停止しゲームBGMを再生
		Sound::GetInstance()->SetStopSound(BOSSBGM);
		Sound::GetInstance()->SetPlayBGM(GAMEBGM, true, Sound::GetInstance()->changevol / 8.0f);
		Sound::GetInstance()->FadeIn(GAMEBGM, 5.0f, Sound::GetInstance()->changevol / 8.0f, true);
	}
	else if (CurrentGameScene == GameScene::State::BossBattle) {

		//ゲームBGMフェードアウト
		Sound::GetInstance()->FadeOut(GAMEBGM, 5.0f, Sound::GetInstance()->changevol / 8.0f, true);

		//ボスBGM
		Sound::GetInstance()->SetPlayBGM(BOSSBGM, true, Sound::GetInstance()->changevol / 5.0f);
		Sound::GetInstance()->FadeIn(BOSSBGM, 5.0f, Sound::GetInstance()->changevol / 5.0f, true);

	}
	else if (CurrentGameScene == GameScene::State::End) {

		//ボスBGMフェードアウト
		Sound::GetInstance()->FadeOut(BOSSBGM, 5.0f, Sound::GetInstance()->changevol / 5.0f, true);
	}

}

/**************************************
停止処理
***************************************/
void SoundGameScene::Stop() {
	Sound::GetInstance()->SetStopSoundOll();

}

/**************************************
シーン取得処理
***************************************/
void SoundGameScene::SetScene(int gamescene) {
	CurrentGameScene = gamescene;
}
