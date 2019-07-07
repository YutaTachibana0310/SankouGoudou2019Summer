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
#include "enemy.h"
#include <vector>
#include <map>

/**************************************
�񋓎q��`
***************************************/
//�G�l�~�[���f���^�C�v
enum class EnemyModelType
{
	Test,		//�e�X�g�p
	Stop,		//��ʊO���猻��Ĉꎞ��~���āA���̌㓦����^�C�v
	Max
};

//�G�l�~�[�^�C�v
enum class EnemyType
{
	Straight,
	Change,
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

	//�G�l�~�[��������
	void SetEnemy();

private:
	std::vector<EnemyModel*> modelContainer;
	std::map<EnemyModelType, IStateMachine<EnemyModel>*> fsm;
	std::map<EnemyType, std::vector<Enemy*>> enemyContainer;
	int cntFrame;

	//�G�l�~�[��������(��������)
	void _SetEnemy(EnemyModelType type, LineTrailModel trailModel);
	void _SetEnemyChange(EnemyModel* model);
};

#endif