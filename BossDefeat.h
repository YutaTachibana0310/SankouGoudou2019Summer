//=====================================
//
//�{�X���j�w�b�_[BossDefeat.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _BOSSDEFEAT_H_
#define _BOSSDEFEAT_H_

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
class BossEnemyModel::BossDefeat : public IStateMachine<BossEnemyModel>
{
public:
	void OnStart(BossEnemyModel* entity);
	int OnUpdate(BossEnemyModel* entity);

private:
	int cntFrame;
	Transform* effect;
	Transform* core;
};

#endif