//=====================================
//
//�X�g���[�g�G�l�~�[���f���w�b�_[StraightEnemyModel.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _STRAIGHTENEMYMODEL_H_
#define _STRAIGHTENEMYMODEL_H_

#include "main.h"
#include "EnemyModel.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class StraightEnemyModel : public EnemyModel
{
public:
	StraightEnemyModel();
	~StraightEnemyModel();

	void Init(LineTrailModel model, int enemyNum);
	int Update();

private:
	const float StartPosZ;
	const float DestPosZ;
};

#endif