//=====================================
//
//�G�l�~�[�o���b�g�R���g���[���w�b�_[EnemyBulletController.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _ENEMYBULLETCONTROLLER_H_
#define _ENEMYBULLETCONTROLLER_H_

#include "main.h"
#include "LineTrailModel.h"

#include <vector>

/**************************************
�O���錾
***************************************/
class EnemyBulletModel;

/**************************************
�N���X��`
***************************************/
class EnemyBulletController
{
public:
	EnemyBulletController();
	~EnemyBulletController();

	void Uninit();
	void Update();
	void Draw();

	void SetEnemyBullet(std::vector<D3DXVECTOR3> emitters, LineTrailModel target);

private:
	std::vector<EnemyBulletModel*> modelContainer;
};

#endif