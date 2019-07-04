//=====================================
//
//プレイヤーバレットコントローラヘッダ[PlayerBulletController.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _PLAYERBULLETCONTROLLER_H_
#define _PLAYERBULLETCONTROLLER_H_

#include "main.h"
#include "LineTrailModel.h"
#include "PlayerBullet.h"
#include <vector>

/**************************************
マクロ定義
***************************************/

/**************************************
PlayerBulletControllerクラス
PlayerBulletを管理する
***************************************/
class PlayerBulletController
{
public:
	PlayerBulletController();
	~PlayerBulletController();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetPlayerBullet(LineTrailModel model);

private:
	std::vector<PlayerBullet*> bulletContainer;
	LPDIRECT3DTEXTURE9 texture;
};

#endif