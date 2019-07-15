//=====================================
//
//�G�l�~�[���[�v�z�[������[EnemyWarpHole.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "EnemyWarpHole.h"

/**************************************
�}�N����`
***************************************/

/**************************************
EnemyWarpHole�R���X�g���N�^
***************************************/
EnemyWarpHole::EnemyWarpHole()
{
	active = false;
}

/**************************************
EnemyWarpHole�f�X�g���N�^
***************************************/
EnemyWarpHole::~EnemyWarpHole()
{

}

/**************************************
EnemyWarpHole����������
***************************************/
void EnemyWarpHole::Init()
{
	cntFrame = 0;
	lifeFrame = RandomRange(30, 100);
	active = true;

	const float PosRange = 5.0f;
	transform.pos.x += RandomRangef(-PosRange, PosRange);
	transform.pos.y += RandomRangef(-PosRange, PosRange);
	transform.pos.z += RandomRangef(-PosRange, PosRange);
}

/**************************************
EnemyWarpHole�X�V����
***************************************/
void EnemyWarpHole::Update()
{
	cntFrame++;
	transform.Rotate(0.0f, 0.0f, 10.0f);

	float t = 1.0f - (float)cntFrame / (float)lifeFrame;
	Animation(t);

	if (cntFrame == lifeFrame)
		Uninit();
}

/**************************************
EnemyWarpHoleEmitter�R���X�g���N�^
***************************************/
EnemyWarpHoleEmitter::EnemyWarpHoleEmitter()
{
	active = false;
}

/**************************************
EnemyWarpHoleEmitter�f�X�g���N�^
***************************************/
EnemyWarpHoleEmitter::~EnemyWarpHoleEmitter()
{

}

/**************************************
EnemyWarpHoleEmitter����������
***************************************/
void EnemyWarpHoleEmitter::Init()
{
	cntFrame = 0;
	duration = RandomRange(10, 20);
	active = true;
}

/**************************************
EnemyWarpHoleEmitter�X�V����
***************************************/
void EnemyWarpHoleEmitter::Update()
{
	cntFrame++;

	if (cntFrame == duration)
		Uninit();
}