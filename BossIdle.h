//=====================================
//
//�{�X�A�C�h���w�b�_[BossIdle.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _BOSSIDLE_H_
#define _BOSSIDLE_H_

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
class BossEnemyModel::BossIdle : public IStateMachine<BossEnemyModel>
{
public:
	void OnStart(BossEnemyModel* entity);
	int OnUpdate(BossEnemyModel* entity);

private:
	int cntFrame;
};

#endif