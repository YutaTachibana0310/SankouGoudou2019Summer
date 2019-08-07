//=====================================
//
//ポストエフェクトマネージャ処理[PostEffectManager.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "PostEffectManager.h"

#include "PostEffect\/SpikeNoiseController.h"
#include "PostEffect\ShockBlurController.h"
#include "PostEffect\BloomController.h"
#include "PostEffect\CrossFilterController.h"
#include "PostEffect\SpeedBlurController.h"

#include "debugTimer.h"

/**************************************
マクロ定義
***************************************/
//#define POSTEFFECT_USE_DEBUG
#define POSTEFFECT_LABEL		"PostEffect"

#ifdef POSTEFFECT_USE_DEBUG
#include "debugWindow.h"
#endif // POSTEFFECT_USE_DEBUG

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/

/**************************************
コンストラクタ
***************************************/
PostEffectManager::PostEffectManager()
{
	useSceneBloom = false;
	useCrossFilter = false;
	useSpeedBlur = true;
}

/**************************************
デストラクタ
***************************************/
PostEffectManager::~PostEffectManager()
{

}

/**************************************
更新処理
***************************************/
void PostEffectManager::Update()
{
#ifdef POSREFFECT_USE_DEBUG
	BeginDebugWindow("SpeedBlur");
	DebugChechBox("Use SpeedBlur", &useSpeedBlur);
	EndDebugWindow("SpeedBlur");
#endif // POSREFFECT_USE_DEBUG

	SpikeNoiseController::Instance()->Update();
	ShockBlurController::Instance()->Update();
	SpeedBlurController::Instance()->Update();

	if (useSceneBloom)
		BloomController::Instance()->Update();

	if (useCrossFilter)
		CrossFilterController::Instance()->Update();
}

/**************************************
描画処理
***************************************/
void PostEffectManager::Draw()
{
	SpikeNoiseController::Instance()->Draw();
	
	ShockBlurController::Instance()->Draw();
	
	if (useSceneBloom)
	{
		BloomController::Instance()->Draw();
	}

	if (useCrossFilter)
	{
		CrossFilterController::Instance()->Draw();
	}

	if (useSpeedBlur)
	{
		SpeedBlurController::Instance()->Draw();
	}
}