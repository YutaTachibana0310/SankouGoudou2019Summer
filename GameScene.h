//=====================================
//
//ゲームシーンヘッダ[GameScene.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include "main.h"
#include "IStateScene.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
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