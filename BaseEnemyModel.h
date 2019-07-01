//=====================================
//
//�x�[�X�G�l�~�[���f���w�b�_[BaseEnemyModel.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _BASEENEMYMODEL_H_
#define _BASEENEMYMODEL_H_

#include "main.h"
#include "IStateMachine.h"
#include "LineTrailModel.h"
#include "Framework\BaseObserver.h"
#include "Framework\ObserveSubject.h"
#include "TrailCollider.h"

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
class BaseEnemyModel : BaseObserver, ObserveSubject
{
public:
	BaseEnemyModel();
	~BaseEnemyModel();

	void Init(LineTrailModel model);
	void Uninit();
	int Update();
	void Draw();
	void ChangeState(IStateMachine<BaseEnemyModel> *next);
	void OnNotified(ObserveSubject *notifier);

	int cntFrame;
	bool active;

private:
	LineTrailModel model;
	TrailCollider *collider;
	IStateMachine<BaseEnemyModel> *state;
	D3DXVECTOR3 pos;

};

#endif