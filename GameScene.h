//=====================================
//
//�Q�[���V�[���w�b�_[GameScene.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include "main.h"
#include "IStateScene.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class GameScene : public IStateScene
{
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	GameScene() {};
	~GameScene() {};
};

#endif