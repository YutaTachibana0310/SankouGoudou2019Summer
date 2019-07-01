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
#include "IStateMachine.h"

/**************************************
マクロ定義
***************************************/
enum EnemyModelResult
{
	StateContinuous,
	AttackTiming,
	StateFinished,
	ResultMax
};

/**************************************
クラス定義
***************************************/
class EnemyModel :public BaseObserver
{
public:
	EnemyModel();
	virtual ~EnemyModel();

	void Init(LineTrailModel model);
	void Uninit();
	int Update();
	void Draw();
	void OnNotified(ObserveSubject *notifier);
	void ChangeState(IStateMachine<EnemyModel> *next);

	int cntFrame;
	bool active;
	TrailCollider *collider;

protected:
	LineTrailModel model;
	D3DXVECTOR3 pos;
	IStateMachine<EnemyModel> *state;
};

#endif