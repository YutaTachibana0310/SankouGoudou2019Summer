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

	BossEnemyActor();
	~BossEnemyActor();

	void Update();
	void Draw();

	void Move(const D3DXVECTOR3& target, int duration);
	void Rotate(const D3DXVECTOR3& target, float magnitude);

	void ChangeAnimation(AnimID next);

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

	void _Move();

	void _Rotate();

public:

};

#endif