//=====================================
//
//サウンドゲームシーンヘッダ[SoundGameScene.h]
//Author:GP12B332 45　渡邉良則
//
//=====================================
#ifndef _SOUNDGAMESCENE_H_
#define _SOUNDGAMESCENE_H_

#include "main.h"
#include "SoundStateScene.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class SoundGameScene : public SoundStateScene
{
public:
	void Play();
	void Stop();

	SoundGameScene() {};
	~SoundGameScene() {};
};

#endif