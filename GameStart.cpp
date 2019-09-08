//=====================================
//
//�Q�[���X�^�[�g����[GameStart.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "GameStart.h"
#include "GameSceneUIManager.h"

/**************************************
�}�N����`
***************************************/
#define GAMESTART_DURATION		(60)

/**************************************
���ꏈ��
***************************************/
void GameScene::GameStart::OnStart(GameScene *entity)
{
	entity->cntFrame = 0;
}

/**************************************
�X�V����
***************************************/
int GameScene::GameStart::OnUpdate(GameScene *entity)
{
	const int TelopTiming = 30;
	const int Duration = 180;

	entity->cntFrame++;

	if(entity->cntFrame == TelopTiming)
		entity->gameSceneUIManager->SetBattleStartTelop();

	entity->UpdateWhole();
	
	if (entity->cntFrame == Duration)
		return GameScene::State::Battle;
	else
		return GameScene::State::Start;
}