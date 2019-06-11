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
	useSceneBloom = true;
	useCrossFilter = false;
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
	SpikeNoiseController::Instance()->Update();
	ShockBlurController::Instance()->Update();

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
}