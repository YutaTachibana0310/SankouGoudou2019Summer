//=====================================
//
//MidiumEnemyModel.h
//機能:中型エネミーモデル
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _MIDIUMENEMYMODEL_H_
#define _MIDIUMENEMYMODEL_H_

#include "main.h"
#include "EnemyModel.h"

#include <vector>

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class MidiumEnemyModel : public EnemyModel
{
public:
	MidiumEnemyModel();

	void Init(std::vector<LineTrailModel>& moveList);
	void Uninit();
	int Update();
	virtual void GetShotPos(std::vector<D3DXVECTOR3>& out);
	void OnNotified(ObserveSubject *notifier);

private:
	enum State
	{
		Wait,
		Moving,
		Damage
	};

	State state;
	UINT step;
	int hp;

	std::vector<LineTrailModel> moveTargetList;

	const float PosZ = 300.0f;
	const float MoveDuration = 60.0f;
	const int EnemyNum = 2;

	D3DXVECTOR3 GetMoveTarget(int i);

	int UpdateOnWait();
	int UpdateOnMoving();
	int UpdateOnDamage();
	void StartMove();
};
#endif