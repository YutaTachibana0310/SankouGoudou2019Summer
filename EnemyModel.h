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

	int cntFrame;
	bool active;
	TrailCollider *collider;

protected:
	LineTrailModel model;
	D3DXVECTOR3 pos;
	IStateMachine<EnemyModel> *state;
};

#endif