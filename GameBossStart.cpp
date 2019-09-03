//=====================================
//
//�e���v���[�g����[GameBossStart.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "GameBossStart.h"
#include "BossUIManager.h"

/**************************************
�}�N����`
***************************************/

/**************************************
���ꏈ��
***************************************/
void GameScene::GameBossStart::OnStart(GameScene * entity)
{
	entity->cntFrame = 0;
	entity->bossUI->SetWarning();
}

/**************************************
�X�V����
***************************************/
int GameScene::GameBossStart::OnUpdate(GameScene * entity)
{
	int result = GameScene::State::BossStart;

	entity->UpdateWhole();

	entity->cntFrame++;

	const int StateDuration = 300;
	if (entity->cntFrame == StateDuration)
	{
		result = GameScene::State::BossBattle;
	}

	return result;
}
