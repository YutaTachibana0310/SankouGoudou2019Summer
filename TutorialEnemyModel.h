//=====================================
//
//TutorialEnemyModel.h
//�@�\:�`���[�g���A���G�l�~�[���f��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _TUTORIALENEMYMODEL_H_
#define _TUTORIALENEMYMODEL_H_

#include "main.h"
#include "EnemyModel.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class TutorialEnemyModel : public EnemyModel
{
public:
	TutorialEnemyModel(LineTrailModel model, int enemyNum);

	int Update();
};
#endif