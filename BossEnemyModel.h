//=====================================
//
//�{�X�G�l�~�[���f���w�b�_[BossEnemyModel.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _BOSSENEMYMODEL_H_
#define _BOSSENEMYMODEL_H_

#include "main.h"
#include "EnemyModel.h"

/**************************************
�}�N����`
***************************************/
class BossEnemyActor;

/**************************************
�N���X��`
***************************************/
class BossEnemyModel : public EnemyModel
{
public:
	BossEnemyModel();
	~BossEnemyModel();

	int Update();
	void Draw();

private:
	BossEnemyActor* actor;
};

#endif