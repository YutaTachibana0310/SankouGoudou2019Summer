//=====================================
//
//ボスコライダーコントローラヘッダ[BossColliderController.h]
//Author:GP12B332 21 立花雄太
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

/**************************************
前方宣言
***************************************/
class BossColliderGuide;
class BossEnemyModel;

/**************************************
マクロ・列挙子定義
***************************************/

/**************************************
クラス定義
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
	std::list<BossColliderGuide*> guideList;
	std::list<TrailCollider*> colliderList;
	BossEnemyModel& model;

	float posZ;
};

#endif