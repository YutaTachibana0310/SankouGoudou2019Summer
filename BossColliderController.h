//=====================================
//
//�{�X�R���C�_�[�R���g���[���w�b�_[BossColliderController.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _BOSSCOLLIDERCONTROLLER_H_
#define _BOSSCOLLIDERCONTROLLER_H_

#include "main.h"
#include "TrailCollider.h"
#include "Framework\BaseObserver.h"
#include "Framework\ObserveSubject.h"

#include <list>
#include <vector>
#include <unordered_map>

/**************************************
�O���錾
***************************************/
class BossColliderGuide;
class BossEnemyModel;

/**************************************
�}�N���E�񋓎q��`
***************************************/

/**************************************
�N���X��`
***************************************/
class BossColliderController : public BaseObserver
{
public:
	BossColliderController(BossEnemyModel& model);
	~BossColliderController();

	void Update();
	void Draw();

	void SetCollider(const std::vector<int>& edgeList);
	void DeleteAll();

	void OnNotified(ObserveSubject* notifier);

private:
	std::list<TrailCollider*> colliderList;
	std::unordered_map<ObserveSubject*, BossColliderGuide*> guideMap;
	std::unordered_map<ObserveSubject*, LineTrailModel> modelMap;
	BossEnemyModel& model;

	float posZ;
};

#endif