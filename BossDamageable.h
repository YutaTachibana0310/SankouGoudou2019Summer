//=====================================
//
//�{�X�_���[�W�G�C�u���w�b�_[BossDamageable.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _BOSSDAMAGEABLE_H_
#define _BOSSDAMAGEABLE_H_

#include "main.h"
#include "BossEnemyModel.h"
#include "IStateMachine.h"

/**************************************
�O���錾
***************************************/

/**************************************
�}�N���E�񋓎q��`
***************************************/

/**************************************
�N���X��`
***************************************/
class BossEnemyModel::BossDamageable: public IStateMachine<BossEnemyModel>
{
public:
	void OnStart(BossEnemyModel *entity);
	int OnUpdate(BossEnemyModel *entity);

private:
	int cntFrame;
};

#endif