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
#include <memory>

/**************************************
�O���錾
***************************************/
class EnemyModel;
class Enemy;
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

	void GetEnemyList(std::list<std::shared_ptr<Enemy>>& out);

private:
	std::list<EnemyModel*> modelList;
};
#endif