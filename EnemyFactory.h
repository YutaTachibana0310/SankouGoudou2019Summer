//=====================================
//
//�G�l�~�[�t�@�N�g���[�w�b�_[EnemyFactory.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _ENEMYFACTORY_H_
#define _ENEMYFACTORY_H_

#include "main.h"
#include "EnemyModel.h"
#include "picojson\picojson.h"
#include "EnemyGuideArrowController.h"

/**************************************
�}�N����`
***************************************/

/**************************************
EnemyFactory�N���X
�p�����
EnemyModel* Crate(picojson::object& data)
void CreateGuide(picojson::object& data, EnemyGuideArrowController* controller)
����������
***************************************/
class EnemyFactory
{
public:
	EnemyFactory() {}
	~EnemyFactory() {}

	virtual EnemyModel* Create(picojson::object& data) = 0;
	virtual void CreateGuide(picojson::object& data, EnemyGuideArrowController* controller) = 0;
};

#endif