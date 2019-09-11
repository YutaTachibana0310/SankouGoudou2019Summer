//=====================================
//
//TutorialEnemyController.h
//�@�\:�`���[�g���A���G�l�~�[�R���g���[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _TUTORIALENEMYCONTROLLER_H_
#define _TUTORIALENEMYCONTROLLER_H_

#include "main.h"
#include <list>
/**************************************
�O���錾
***************************************/
class EnemyModel;

/**************************************
�N���X��`
***************************************/
class TutorialEnemyController
{
public:
	TutorialEnemyController();
	~TutorialEnemyController();

	void Update();
	void Draw();

	bool IsExistEnemy();

private:
	std::list<EnemyModel*> modelList;
};
#endif