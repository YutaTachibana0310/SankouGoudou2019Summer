//=====================================
//
//�`�F���W�G�l�~�[�t�@�N�g���[�w�b�_[ChangeEnemyFactory.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _CHANGEENEMYFACTORY_H_
#define _CHANGEENEMYFACTORY_H_

#include "main.h"
#include "EnemyFactory.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class ChangeEnemyFactory : public EnemyFactory
{
public:
	ChangeEnemyFactory() {}
	~ChangeEnemyFactory() {}

	EnemyModel* Create(picojson::object& data);
	void CreateGuide(picojson::object& data, EnemyGuideArrowController* controller);
};

#endif