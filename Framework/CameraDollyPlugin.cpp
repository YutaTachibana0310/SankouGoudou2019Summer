//=====================================
//
//CameraDollyPlugin.cpp
//機能:カメラドーリープラグイン
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "CameraDollyPlugin.h"
#include "Easing.h"
#include "Vector3.h"

/**************************************
グローバル変数
***************************************/

/**************************************
更新処理
***************************************/
void Camera::DollyPlugin::Update()
{
	if (cntFrame >= duration)
		return;

	cntFrame++;
}

/**************************************
プラグイン適用処理
***************************************/
void Camera::DollyPlugin::Apply(Camera & camera)
{
	//距離の変化量をイージングで求める
	if (cntFrame < duration)
	{
		float t = 1.0f * cntFrame / duration;
		currentLength = Easing::EaseValue(t, startLength, deltaLength, EaseType::OutCubic);
	}

	//カメラ視点に距離の変化量を加える
	camera.eyeWork += currentLength;
}

/**************************************
セット処理
***************************************/
void Camera::DollyPlugin::Set(const D3DXVECTOR3 & deltaLegnth, int duration)
{
	this->cntFrame = 0;
	this->deltaLength = deltaLegnth;
	this->startLength = this->currentLength;
	this->duration = duration;
}

/**************************************
コンストラクタ
***************************************/
Camera::DollyPlugin::DollyPlugin() :
	cntFrame(0),
	deltaLength(Vector3::Zero),
	startLength(Vector3::Zero),
	currentLength(Vector3::Zero),
	duration(0)
{

}