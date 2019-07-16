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