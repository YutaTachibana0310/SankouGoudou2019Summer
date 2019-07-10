//=====================================
//
//サウンドリザルトシーンヘッダ[SoundResultScene.h]
//Author:GP12B332 45　渡邉良則
//
//=====================================
#ifndef _SOUNDRESULTSCENE_H_
#define _SOUNDRESULTSCENE_H_

#include "main.h"
#include "SoundStateScene.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class SoundResultScene : public SoundStateScene
{
public:
	void Play();
	void Stop();

	SoundResultScene() {};
	~SoundResultScene() {};
};

#endif
