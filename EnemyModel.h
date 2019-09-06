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
#include <memory>

class BaseEmitter;
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

#define ENEMY_NUM_OUTERLINE		(3)		//�܊p�`�̊O���ɐ�������G�l�~�[�̐�
#define ENEMY_NUM_INNNERLINE	(5)		//�܊p�`�̓����ɐ�������G�l�~�[�̐�

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
	virtual void GetEnemy(std::list<std::shared_ptr<Enemy>>& out);
	virtual void CheckDestroied();
	virtual void GetShotPos(std::vector<D3DXVECTOR3>& out);

	int cntFrame;
	bool active;
	TrailCollider *collider;
	LineTrailModel model;
	std::vector<std::shared_ptr<Enemy>> enemyList;
	std::vector<BaseEmitter*> chageEffectList;

	//�܊p�`�̊O�����\������LineModel
	static const std::vector<LineTrailModel> OuterLineModel;

protected:
	D3DXVECTOR3 pos;
	const D3DXVECTOR3 ShotPosOffset = D3DXVECTOR3(0.0f, 0.0f, -50.0f);

};

#endif