//=====================================
//
//MidiumEnemyFactory.h
//�@�\:���^�G�l�~�[���쐬����t�@�N�g���N���X
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _MIDIUMENEMYFACTORY_H_
#define _MIDIUMENEMYFACTORY_H_

#include "main.h"
#include "EnemyFactory.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class MidiumEnemyFactory : public EnemyFactory
{
	using EnemyFactory::EnemyFactory;
public:
	EnemyModel * Create(picojson::object& data);
	void CreateGuide(picojson::object & data, EnemyGuideArrowController* container);
};
#endif