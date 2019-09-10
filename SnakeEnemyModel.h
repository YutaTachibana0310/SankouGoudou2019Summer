//=====================================
//
//�X�l�[�N�G�l�~�[���f���w�b�_[SnakeEnemyModel.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _SNAKEENEMYMODEL_H_
#define _SNAKEENEMYMODEL_H_

#include "main.h"
#include "EnemyModel.h"

#include <map>

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class SnakeEnemyModel : public EnemyModel
{
public:
	SnakeEnemyModel() {}
	~SnakeEnemyModel();

	void Init(std::vector<int> destList);
	int Update();
	void OnNotified(ObserveSubject *notifier);

private:
	std::vector<TrailCollider*> colliderList;
	std::vector<D3DXVECTOR3> moveTargetList;
	std::vector<float> timeList;
	std::map<UINT, std::list<std::weak_ptr<Enemy>>> colliderMap;

	void SwapInColliderMap(TrailCollider *current, TrailCollider *next, std::shared_ptr<Enemy> enemy);
};

#endif