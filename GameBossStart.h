//=====================================
//
//�Q�[���{�X�X�^�[�g�w�b�_[GameBossStart.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _GAMEBOSSSTART_H_
#define _GAMEBOSSSTART_H_

#include "main.h"
#include "IStateMachine.h"
#include "GameScene.h"

/**************************************
�O���錾
***************************************/

/**************************************
�}�N���E�񋓎q��`
***************************************/

/**************************************
�N���X��`
***************************************/
class GameScene::GameBossStart : public IStateMachine<GameScene>
{
public:
	void OnStart(GameScene* entity);
	int OnUpdate(GameScene* entity);
};

#endif