//=====================================
//
//�X�g�b�v�G�l�~�[���f���w�b�_[StopEnemyModel.h]
//�ꎞ��~����^�C�v�̃G�l�~�[���f��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _STOPENEMYMODEL_H_
#define _STOPENEMYMODEL_H_

#include "main.h"
#include "EnemyModel.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class StopEnemyModel : public IStateMachine<EnemyModel>
{
public:
	void OnStart(EnemyModel *entity);
	int OnUpdate(EnemyModel *entity);
	void OnExit(EnemyModel *entity);
};

#endif