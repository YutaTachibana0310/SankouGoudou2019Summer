//=====================================
//
//�G�l�~�[�R���g���[���[�w�b�_[EnemyController.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _ENEMYCONTROLLER_H_
#define _ENEMYCONTROLLER_H_

#include "main.h"
#include "EnemyModel.h"
#include "IStateMachine.h"
#include "enemy.h"
#include "StageModel.h"
#include "EnemyBulletController.h"

#include "Framework\BaseObserver.h"
#include "picojson\picojson.h"

#include <list>
#include <vector>

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
	std::list<EnemyModel*> modelList;
	int cntFrame;

	std::vector<StageModel> stageModelList;
	int currentIndex;

	EnemyBulletController* bulletController;

	//�G�l�~�[��������(��������)
	EnemySnake *test;
	void _SetEnemyChange(picojson::object& data);
	void _SetEnemyStraight(picojson::object& data);
	void _SetEnemySnake(picojson::object& data);

	//�X�e�[�W�f�[�^�ǂݍ��ݏ���
	bool LoadStageData();

	//�U������
	void EnemyAttack(EnemyModel* model);

	//�U���`���[�W����
	void SetChageEffect(EnemyModel *model);

	//�܊p�`�̊O�����\������LineModel
	static const std::vector<LineTrailModel> OuterLineModel;
};

#endif