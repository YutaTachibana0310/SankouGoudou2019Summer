//=====================================
//
//�e�X�g�G�l�~�[���f���w�b�_[TestEnemyModel.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _TESTENEMYMODEL_H_
#define _TESTENEMYMODEL_H_

#include "main.h"
#include "IStateMachine.h"
#include "EnemyModel.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class TestEnemyModel : public IStateMachine<EnemyModel>
{
public:
	void OnStart(EnemyModel *entity);
	int OnUpdate(EnemyModel *entity);
	void OnExit(EnemyModel *entity);
};

#endif