//=====================================
//
//ポストエフェクトマネージャヘッダ[PostEffectManager.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _POSTEFFECTMANAGER_H_
#define _POSTEFFECTMANAGER_H_

#include "main.h"
#include "PostEffect\ScreenObject.h"
#include "Framework\BaseSingleton.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class PostEffectManager : public BaseSingleton<PostEffectManager>
{
public:
	friend class BaseSingleton<PostEffectManager>;

	static void Destroy();
	void Update();
	void Draw();

private:
	PostEffectManager();
	~PostEffectManager();

	bool useSceneBloom;
	bool useCrossFilter;
	bool useSpeedBlur;
};


#endif