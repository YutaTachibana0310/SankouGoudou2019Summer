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
#include "EnemyFactory.h"
#include "enemy.h"
#include "StageModel.h"
#include "EnemyBulletController.h"
#include "EnemyGuideArrowController.h"

#include "Framework\BaseObserver.h"
#include "picojson\picojson.h"

#include <list>
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
	void DrawGuide();

	//�G�l�~�[��������
	void SetEnemy();

	//�G�l�~�[���W�擾����
	void GetEnemyPositionList(std::vector<D3DXVECTOR3>& out);

private:
	std::list<EnemyModel*> modelList;
	int cntFrame;

	std::vector<StageModel> stageModelList;
	int currentIndex;

	EnemyBulletController* bulletController;
	EnemyGuideArrowController* guideController;

	//�G�l�~�[�����N���X�R���e�i
	std::map<std::string, EnemyFactory*> factoryContainer;

	//test
	EnemySnake *test;

	//�X�e�[�W�f�[�^�ǂݍ��ݏ���
	bool LoadStageData();

	//�U������
	void EnemyAttack(EnemyModel* model);

	//�U���`���[�W����
	void SetChageEffect(EnemyModel *model);

	//�K�C�h��������
	void SetGuide();
};

#endif