//=====================================
//
//�{�X�S�؃A�^�b�N�w�b�_[BossRebarAttack.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _BOSSREBARATTACK_H_
#define _BOSSREBARATTACK_H_

#include "main.h"
#include "IStateMachine.h"
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
class BossEnemyModel::BossRebarAttack : public IStateMachine<BossEnemyModel>
{
public:
	void OnStart(BossEnemyModel *entity);
	int OnUpdate(BossEnemyModel *entity);

private:
	int cntFrame;
	int cntLoop;
};

#endif