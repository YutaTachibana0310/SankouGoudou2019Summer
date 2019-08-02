//=====================================
//
//ベースエネミーモデルヘッダ[BaseEnemyModel.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BASEENEMYMODEL_H_
#define _BASEENEMYMODEL_H_

#include "main.h"
#include "LineTrailModel.h"
#include "Framework\BaseObserver.h"
#include "TrailCollider.h"
#include "LineRenderer.h"
#include "enemy.h"

#include <vector>

class BaseEmitter;
/**************************************
マクロ定義
***************************************/
enum EnemyModelResult
{
	StateContinuous,
	AttackTiming,
	StateFinished,
	ChargeTiming,
	ResultMax
};

#define ENEMY_NUM_OUTERLINE		(3)		//五角形の外周に生成するエネミーの数
#define ENEMY_NUM_INNNERLINE	(5)		//五角形の内側に生成するエネミーの数

/**************************************
EnemyModelクラス
継承先で必ずint Update()を実装する
必要であればInit(LineTrailModel)をoverrideする
***************************************/
class EnemyModel :public BaseObserver
{
public:
	EnemyModel();
	virtual ~EnemyModel();

	virtual void Init(LineTrailModel model);
	virtual void Uninit();
	virtual int Update() = 0;
	virtual void Draw();

	virtual void OnNotified(ObserveSubject *notifier);

	int cntFrame;
	bool active;
	TrailCollider *collider;
	LineTrailModel model;
	std::vector<Enemy*> enemyList;
	std::vector<BaseEmitter*> chageEffectList;

	//五角形の外周を構成するLineModel
	static const std::vector<LineTrailModel> OuterLineModel;

protected:
	D3DXVECTOR3 pos;

};

#endif