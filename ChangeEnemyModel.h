//=====================================
//
//�X�g�b�v�G�l�~�[���f���w�b�_[StopEnemyModel.h]
//�ꎞ��~����^�C�v�̃G�l�~�[���f��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _CHANGEENEMYMODEL_H_
#define _CHANGEENEMYMODEL_H_

#include "main.h"
#include "EnemyModel.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class ChangeEnemyModel : public EnemyModel
{
public:
	ChangeEnemyModel();
	~ChangeEnemyModel();

	void Init(LineTrailModel model);
	int Update();
};

#endif