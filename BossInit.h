//=====================================
//
//�{�X������ԃw�b�_[BossInit.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _BOSSINIT_H_
#define _BOSSINIT_H_

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
class BossEnemyModel::BossInit : public IStateMachine<BossEnemyModel>
{
public:
	void OnStart(BossEnemyModel* entity);
	int OnUpdate(BossEnemyModel* entity);

private:
	int cntFrame;
};

#endif