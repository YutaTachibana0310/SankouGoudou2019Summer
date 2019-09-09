//=====================================
//
//CameraDollyPlugin.h
//機能:カメラドーリープラグイン
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _CAMERADOLLYPLUGIN_H_
#define _CAMERADOLLYPLUGIN_H_

#include "../Camera.h"
#include "BaseSingleton.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class Camera::DollyPlugin : public BaseCameraPlugin, public BaseSingleton<DollyPlugin>
{
	friend class BaseSingleton<DollyPlugin>;
public:
	void Update();
	void Apply(Camera& camera);
	void Set(const D3DXVECTOR3& deltaLegnth, int duration);

private:
	int cntFrame;
	D3DXVECTOR3 deltaLength;
	int duration;

	DollyPlugin();
};

#endif