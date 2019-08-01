//=====================================
//
//�X�g���[�g�G�l�~�[�t�@�N�g���[�w�b�_[StraightEnemyFactory.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _STRAIGHTENEMYFACTORY_H_
#define _STRAIGHTENEMYFACTORY_H_

#include "main.h"
#include "EnemyFactory.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class StraightEnemyFactory : public EnemyFactory
{
public:
	StraightEnemyFactory() {}
	~StraightEnemyFactory() {}

	EnemyModel* Create(picojson::object& data);
	void CreateGuide(picojson::object& data, EnemyGuideArrowController* controller);
};


#endif