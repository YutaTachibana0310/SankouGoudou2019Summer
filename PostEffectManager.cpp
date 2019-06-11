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
	useSceneBloom = true;
	useCrossFilter = false;
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
	SpikeNoiseController::Instance()->Update();
	ShockBlurController::Instance()->Update();

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
}