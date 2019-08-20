//=====================================
//
//ボスコントローラヘッダ[BossController.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BOSSCONTROLLER_H_
#define _BOSSCONTROLLER_H_

#include "main.h"
#include "BossEnemyModel.h"
#include "EnemyBulletController.h"

/**************************************
前方宣言
***************************************/

/**************************************
マクロ・列挙子定義
***************************************/

/**************************************
クラス定義
***************************************/
class BossController
{
public:
	BossController(const Transform& player);
	~BossController();

	void Update();
	void Draw();

	void SetActive(bool state);

private:
	bool active;
	BossEnemyModel *bossModel;
};

#endif