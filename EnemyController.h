//=====================================
//
//エネミーコントローラーヘッダ[EnemyController.h]
//Author:GP12B332 21 立花雄太
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
列挙子定義
***************************************/
//エネミーモデルタイプ
enum class EnemyModelType
{
	Test,		//テスト用
	Stop,		//画面外から現れて一時停止して、その後逃げるタイプ
	Max
};

//エネミータイプ
enum class EnemyType
{
	Straight,
	Change,
	Max
};

/**************************************
クラス定義
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

	//エネミー生成処理
	void SetEnemy();

	//エネミー座標取得処理
	void GetEnemyPositionList(std::vector<D3DXVECTOR3>& out);

private:
	std::list<EnemyModel*> modelList;
	int cntFrame;

	std::vector<StageModel> stageModelList;
	int currentIndex;

	EnemyBulletController* bulletController;
	EnemyGuideArrowController* guideController;

	//エネミー生成クラスコンテナ
	std::map<std::string, EnemyFactory*> factoryContainer;

	//test
	EnemySnake *test;

	//ステージデータ読み込み処理
	bool LoadStageData();

	//攻撃処理
	void EnemyAttack(EnemyModel* model);

	//攻撃チャージ処理
	void SetChageEffect(EnemyModel *model);

	//ガイド生成処理
	void SetGuide();
};

#endif