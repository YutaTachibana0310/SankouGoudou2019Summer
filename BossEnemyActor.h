//=====================================
//
//�{�X�G�l�~�[�A�N�^�[�w�b�_[BossEnemyActor.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _BOSSENEMYACTOR_H_
#define _BOSSENEMYACTOR_H_

#include "main.h"

/**************************************
�O���錾
***************************************/
class AnimationManager;

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
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