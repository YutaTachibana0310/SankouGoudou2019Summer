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

}

/**************************************
停止処理
***************************************/
void SoundTitleScene::Stop() {
	Sound::GetInstance()->SetStopSound();
}