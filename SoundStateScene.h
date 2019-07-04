//=====================================
//
//サウンドステートシーンヘッダ[SoundStateScene.h]
//Author:GP12B332 45　渡邉良則
//
//=====================================
#ifndef _SOUNDSTATESCENE_H_
#define _SOUNDSTATESCENE_H_

#include "main.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class SoundStateScene
{
public:
	virtual void Play() = 0;
	virtual void Stop() = 0;


	SoundStateScene() {};
	virtual ~SoundStateScene() {};
};

#endif
