//=====================================
//
//プレイヤーバレットヘッダ[PlayerBullet.h]
//Author:GP12B332 21 立花
//
//=====================================
#ifndef _PLAYERBULLET_H_
#define _PLAYERBULLET_H_

#include "main.h"
#include "Framework\BaseObserver.h"
#include "TrailCollider.h"
#include "LineTrailModel.h"
#include "Framework\BoxCollider3D.h"
#include "Framework\ColliderObserver.h"

/**************************************
マクロ定義
***************************************/

/**************************************
構造体定義
***************************************/

/**************************************
プロトタイプ宣言
***************************************/
class PlayerBullet : public ColliderObserver, public BaseObserver
{
public:
	PlayerBullet();							//コンストラクタ
	~PlayerBullet();						//デストラクタ

	void Init(LineTrailModel model);		//初期化処理
	void Uninit();							//終了処理
	void Update();							//更新処理
	void Draw();							//描画処理

	void OnNotified(ObserveSubject *notifier);
	void OnNotified(BoxCollider3DTag other);
	bool active;
	bool isDestroyed;

private:
	D3DXVECTOR3 pos;
	TrailCollider *collider;
	BoxCollider3D *colliderR, *colliderL;
	LPDIRECT3DVERTEXBUFFER9 vtxBuff;
	int cntFrame;
	D3DXVECTOR3 vtxUp;
	D3DXVECTOR3 edgeR, edgeL;

	void SetEdgePos(LineTrailModel model);

};

#endif