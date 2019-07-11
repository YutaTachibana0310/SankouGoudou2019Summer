//=====================================
//
//�x�[�X�G�l�~�[���f���w�b�_[BaseEnemyModel.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _BASEENEMYMODEL_H_
#define _BASEENEMYMODEL_H_

#include "main.h"
#include "LineTrailModel.h"
#include "Framework\BaseObserver.h"
#include "TrailCollider.h"
#include "IStateMachine.h"
#include "LineRenderer.h"
#include "enemy.h"

#include <vector>

/**************************************
�}�N����`
***************************************/
enum EnemyModelResult
{
	StateContinuous,
	AttackTiming,
	StateFinished,
	ResultMax
};

/**************************************
�N���X��`
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
	void AddEnemy(Enemy* enemy);

	int cntFrame;
	bool active;
	TrailCollider *collider;
	LineTrailModel model;
	std::vector<Enemy*> enemyList;

protected:
	D3DXVECTOR3 pos;
	IStateMachine<EnemyModel> *state;

};

#endif