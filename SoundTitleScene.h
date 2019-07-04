//=====================================
//
//サウンドタイトルシーンヘッダ[SoundTitleScene.h]
//Author:GP12B332 45　渡邉良則
//
//=====================================
#ifndef _SOUNDTITLESCENE_H_
#define _SOUNDTITLESCENE_H_

#include "main.h"
#include "SoundStateScene.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class SoundTitleScene : public SoundStateScene
{
public:
	void Play();
	void Stop();

	SoundTitleScene() {};
	~SoundTitleScene() {};
};

#endif