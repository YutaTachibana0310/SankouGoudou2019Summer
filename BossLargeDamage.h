//=====================================
//
//�{�X��_���[�W�w�b�_[BassLargeDamage.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _BOSSLARGEDAMAGE_H_
#define _BOSSLARGEDAMAGE_H_

#include "main.h"
#include "IStateMachine.h"
#include "BossEnemyModel.h"

/**************************************
�O���錾
***************************************/
class BossEnemyModel;

/**************************************
�}�N���E�񋓎q��`
***************************************/

/**************************************
�N���X��`
***************************************/
class BossEnemyModel::BossLargeDamage : public IStateMachine<BossEnemyModel>
{
public:
	void OnStart(BossEnemyModel* entity);
	int OnUpdate(BossEnemyModel* entity);

private:
	int cntFrame;
};

#endif