//=====================================
//
//コライダーオブザーバーヘッダ[ColliderObserver.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _COLLIDEROBSERVER_H_
#define _COLLIDEROBSERVER_H_

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
enum class BoxCollider3DTag;

class ColliderObserver
{
public:
	virtual void OnNotified(BoxCollider3DTag other) = 0;
};

#endif