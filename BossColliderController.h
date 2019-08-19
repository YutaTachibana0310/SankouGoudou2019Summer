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

#include <list>
#include <vector>

/**************************************
前方宣言
***************************************/
class BossColliderGuide;

/**************************************
マクロ・列挙子定義
***************************************/

/**************************************
クラス定義
***************************************/
class BossColliderController
{
public:
	BossColliderController();
	~BossColliderController();

	void Update();
	void Draw();

	void SetCollider(const std::vector<int>& edgeList);
	void DeleteAll();

private:
	std::list<BossColliderGuide*> guideList;
	std::list<TrailCollider*> colliderList;

	float posZ;
};

#endif