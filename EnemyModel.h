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
	ChargeTiming,
	ResultMax
};

/**************************************
EnemyModel�N���X
�p����ŕK��int Update()����������
�K�v�ł����Init(LineTrailModel)��override����
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

protected:
	D3DXVECTOR3 pos;

};

#endif