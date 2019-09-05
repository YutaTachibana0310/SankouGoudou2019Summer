//=====================================
//
//エネミーバレットコントローラヘッダ[EnemyBulletController.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _ENEMYBULLETCONTROLLER_H_
#define _ENEMYBULLETCONTROLLER_H_

#include "main.h"
#include "LineTrailModel.h"

#include <vector>

/**************************************
前方宣言
***************************************/
class EnemyBulletModel;

/**************************************
クラス定義
***************************************/
class EnemyBulletController
{
public:
	EnemyBulletController();
	~EnemyBulletController();

	void Uninit();
	void Update();
	void Draw();

	void Set(std::vector<D3DXVECTOR3> emitters, LineTrailModel target);
	void Set(std::vector<D3DXVECTOR3> emitters, LineTrailModel target, int duration, const D3DXVECTOR3 scale);
	void DisableAll();

private:
	std::vector<EnemyBulletModel*> modelContainer;
};

#endif