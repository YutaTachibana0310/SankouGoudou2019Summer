//=====================================
//
//カメラヘッダ[Camera.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"
#include "Framework/BaseSingleton.h"
#include "Framework/Transform.h"

#include <vector>

class BaseCameraPlugin;
/**************************************
Cameraクラス
***************************************/
class Camera : public BaseSingleton<Camera>
{
	friend class BaseSingleton<Camera>;
public:
	void Init();		//初期化
	void Update();		//更新
	void Set();			//カメラ情報反映処理

protected:
	//SRT情報
	Transform transform;

	//注視点
	D3DXVECTOR3 target;

	//視点、注視点、上方向（作業用領域）
	D3DXVECTOR3 eyeWork;
	D3DXVECTOR3 targetWork;
	D3DXVECTOR3 upWork;

	//視野角、アスペクト比、ニア値、ファー値
	float viewAngle;
	float viewAspect;
	float viewNear;
	float viewFar;

	//プラグインリスト
	std::vector<BaseCameraPlugin*> pluginList;

private:
	Camera();
	Camera(const Camera&) {}
	~Camera() {}

public:
	//カメラを揺らすプラグイン
	class ShakePlugin;

};

/**************************************
カメラプラグイン基底クラス
***************************************/
class BaseCameraPlugin
{
public:
	virtual void Update() = 0;
	virtual void Apply(Camera& camera) = 0;
};

#endif