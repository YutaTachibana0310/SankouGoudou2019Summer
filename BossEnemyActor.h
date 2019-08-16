//=====================================
//
//ボスエネミーアクターヘッダ[BossEnemyActor.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BOSSENEMYACTOR_H_
#define _BOSSENEMYACTOR_H_

#include "main.h"

/**************************************
前方宣言
***************************************/
class AnimationManager;

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class BossEnemyActor
{
public:
	BossEnemyActor();
	~BossEnemyActor();

	void Update();
	void Draw();

	void Move(const D3DXVECTOR3& target, int duration);
	void Rotate(float angle, int duration);

private:
	AnimationManager* animManager;
	Transform transform;
	int cntFrame;

	bool inMoving;
	D3DXVECTOR3 prevPos, targetPos;
	int cntMove, durationMove;

	bool inRotaiton;
	float rotAngle;
	int cntRotate, durationRotate;

	void _Move();

	void _Rotate();

public:
	enum AnimID
	{
		Attack01,
		Attack02,
		Damage,
		Death,
		Flying,
		Idle,
		Max
	};
};

#endif