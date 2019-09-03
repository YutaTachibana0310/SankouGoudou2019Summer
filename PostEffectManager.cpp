//=====================================
//
//�|�X�g�G�t�F�N�g�}�l�[�W������[PostEffectManager.cpp]
//Author:GP12B332 21 ���ԗY��
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
�}�N����`
***************************************/
//#define POSTEFFECT_USE_DEBUG
#define POSTEFFECT_LABEL		"PostEffect"

#ifdef POSTEFFECT_USE_DEBUG
#include "debugWindow.h"
#endif // POSTEFFECT_USE_DEBUG

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
PostEffectManager::PostEffectManager()
{
	useSceneBloom = false;
	useCrossFilter = false;
	useSpeedBlur = true;
}

/**************************************
�f�X�g���N�^
***************************************/
PostEffectManager::~PostEffectManager()
{

}

/**************************************
�X�V����
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
�`�揈��
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