//=====================================
//
//エネミーバレットヘッダ[EnemyBullet.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _ENEMYBULLET_H_
#define _ENEMYBULLET_H_

#include "main.h"
#include "Framework\BoardPolygon.h"

/**************************************
マクロ定義
***************************************/
#define RESOURCE_ENEMYBULLET_TAG	("EnemyBullet")

class EnemyBulletTrailEmitter;	
/**************************************
クラス定義
***************************************/
class EnemyBullet
{
public:
	EnemyBullet();
	~EnemyBullet();

	void Init(D3DXVECTOR3 setPos, D3DXVECTOR3 target, int reachFrame, const D3DXVECTOR3& scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	void Uninit();
	void Update();
	void Draw();

	Transform transform;
	bool active;

private:
	int cntFrame;
	BoardPolygon *polygon;
	D3DXVECTOR3 targetPos;
	D3DXVECTOR3 velocity;

	EnemyBulletTrailEmitter *trail;
};

#endif