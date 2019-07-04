//=====================================
//
//サウンドリザルトシーン処理[SoundResultScene.cpp]
//Author:GP12B332 45　渡邉良則
//
//=====================================

#include "sound.h"
#include "SoundResultScene.h"
#include "input.h"

/**************************************
再生処理
***************************************/
void SoundResultScene::Play() {

}

/**************************************
停止処理
***************************************/
void SoundResultScene::Stop() {
	Sound::GetInstance()->SetStopSound();
}