//=====================================
//
//�G�l�~�[�R���g���[���[�w�b�_[EnemyController.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _ENEMYCONTROLLER_H_
#define _ENEMYCONTROLLER_H_

#include "main.h"
#include "Framework\BaseObserver.h"
#include "EnemyModel.h"
#include "IStateMachine.h"
#include <vector>
#include <map>

/**************************************
�񋓎q��`
***************************************/
enum class EnemyType
{
	Test,
	Max
};

/**************************************
�N���X��`
***************************************/
class EnemyController
{
public:
	EnemyController();
	~EnemyController();

	void Init();
	void Uninit();
	void Update();
	void Draw();

private:
	std::vector<EnemyModel*> modelContainer;
	std::map<EnemyType, IStateMachine<EnemyModel>*> fsm;
};

#endif