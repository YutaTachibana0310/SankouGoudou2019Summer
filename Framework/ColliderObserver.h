//=====================================
//
//コライダーオブザーバーヘッダ[ColliderObserver.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _COLLIDEROBSERVER_H_
#define _COLLIDEROBSERVER_H_

#include "BoxCollider3D.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class ColliderObserver
{
public:
	virtual void OnNotify(BoxCollider3DTag other) = 0;
};

#endif