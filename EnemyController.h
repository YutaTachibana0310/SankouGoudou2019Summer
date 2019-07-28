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
#include "enemy.h"
#include "StageModel.h"

#include "Framework\BaseObserver.h"
#include "picojson\picojson.h"

#include <list>
#include <vector>

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

	//エネミー生成処理
	void SetEnemy();

private:
	std::list<EnemyModel*> modelList;
	int cntFrame;

	std::vector<StageModel> stageModelList;
	int currentIndex;

	//エネミー生成処理(内部処理)
	
	void _SetEnemyChange(picojson::object& data);
	void _SetEnemyStraight(picojson::object& data);

	//test
	EnemySnake *test;

	//ステージデータ読み込み処理
	bool LoadStageData();
};

#endif