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
	enum AnimID
	{
		Flying,
		Attack01,
		Attack02,
		Damage,
		Defeat,
		Idle,
		LargeDamage,
		Max

	};

	BossEnemyActor();
	~BossEnemyActor();

	void Update();
	void Draw();

	void Move(const D3DXVECTOR3& target, int duration);
	void Rotate(const D3DXVECTOR3& target, float magnitude);

	void ChangeAnimation(AnimID next);

	void SetWriteableZ(bool state);
	void SetActive(bool state);

	D3DXVECTOR3 GetActorPosition();

	Transform transform;

private:
	AnimationManager* animManager;
	int cntFrame;

	bool inMoving;
	D3DXVECTOR3 prevPos, targetPos;
	int cntMove, durationMove;

	bool inRotaiton;
	D3DXVECTOR3 targetForward;
	float magnitudeRotate;

	bool writeableZ;

	bool active;

	void _Move();

	void _Rotate();

public:

};

#endif