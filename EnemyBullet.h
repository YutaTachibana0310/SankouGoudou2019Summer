//=====================================
//
//�G�l�~�[�o���b�g�w�b�_[EnemyBullet.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _ENEMYBULLET_H_
#define _ENEMYBULLET_H_

#include "main.h"
#include "Framework\BoardPolygon.h"

/**************************************
�}�N����`
***************************************/
#define RESOURCE_ENEMYBULLET_TAG	("EnemyBullet")

/**************************************
�N���X��`
***************************************/
class EnemyBullet
{
public:
	EnemyBullet();
	~EnemyBullet();

	void Init(D3DXVECTOR3 setPos, D3DXVECTOR3 target, int reachFrame);
	void Uninit();
	void Update();
	void Draw();

	Transform transform;
	bool active;

private:
	int cntFrame;
	int reachFrame;
	BoardPolygon *polygon;
	D3DXVECTOR3 targetPos;
	D3DXVECTOR3 velocity;
};

#endif