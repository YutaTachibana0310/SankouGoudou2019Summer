//=====================================
//
//�Q�[���{�X�o�g���w�b�_[GameBossBattle.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _GAMEBOSSBATTLE_H_
#define _GAMEBOSSBATTLE_H_

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
class GameScene::GameBossBattle : public IStateMachine<GameScene>
{
public:
	void OnStart(GameScene* entity);
	int OnUpdate(GameScene* entity);
};

#endif