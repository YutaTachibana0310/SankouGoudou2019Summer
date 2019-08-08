//=====================================
//
//エネミーバレットモデルヘッダ[EnemyBulletModel.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _ENEMYBULLETMODEL_H_
#define _ENEMYBULLETMODEL_H_

#include "main.h"
#include "LineTrailModel.h"
#include "TrailCollider.h"

#include <vector>

/**************************************
前方宣言
***************************************/
class EnemyBullet;

/**************************************
クラス定義
***************************************/
class EnemyBulletModel
{
public:
	EnemyBulletModel();
	~EnemyBulletModel();

	void Init(std::vector<D3DXVECTOR3> emitters, LineTrailModel target);
	void Uninit();
	void Update();
	void Draw();
	void Disable();

	bool active;

private:
	std::vector<EnemyBullet*> bullets;
	int cntFrame;
	TrailCollider *collider;
	float posZ;
	LineTrailModel targetLine;
};

#endif