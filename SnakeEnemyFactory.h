//=====================================
//
//�X�l�[�N�G�l�~�[�t�@�N�g���[�w�b�_[SnakeEnemyFactory.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _SNAKEENEMYFACTORY_H_
#define _SNAKEENEMYFACTORY_H_

#include "main.h"
#include "EnemyFactory.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class SnakeEnemyFactory : public EnemyFactory
{
public:
	SnakeEnemyFactory() {}
	~SnakeEnemyFactory() {}

	EnemyModel* Create(picojson::object& data) override;
	void CreateGuide(picojson::object& data, EnemyGuideArrowController* controller) override;
};

#endif