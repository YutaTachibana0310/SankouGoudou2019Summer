//=====================================
//
//�{�X�z�[�~���O�A�^�b�N�w�b�_[BossHomingAttack.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _BOSSHOMINGATTACK_H_
#define _BOSSHOMINGATTACK_H_

#include "main.h"
#include "BossEnemyModel.h"

/**************************************
�O���錾
***************************************/

/**************************************
�}�N���E�񋓎q��`
***************************************/

/**************************************
�N���X��`
***************************************/
class BossEnemyModel::BossHomingAttack : public IStateMachine<BossEnemyModel>
{
public:
	void OnStart(BossEnemyModel* entity);
	int OnUpdate(BossEnemyModel* entity);

private:
	int cntFrame;
};

#endif