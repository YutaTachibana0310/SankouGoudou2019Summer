//=====================================
//
//スネークエネミーモデルヘッダ[SnakeEnemyModel.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _SNAKEENEMYMODEL_H_
#define _SNAKEENEMYMODEL_H_

#include "main.h"
#include "EnemyModel.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class SnakeEnemyModel : public EnemyModel
{
public:
	SnakeEnemyModel() {}
	~SnakeEnemyModel() {}

	void Init(std::vector<int> destList);
	int Update();
	void Draw();
	//void OnNotified(ObserveSubject *notifier);

private:
	std::vector<TrailCollider*> colliderList;
	std::vector<D3DXVECTOR3> moveTargetList;
	
};

#endif