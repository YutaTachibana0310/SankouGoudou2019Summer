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

/**************************************
マクロ定義
***************************************/

/**************************************
構造体定義
***************************************/

/**************************************
プロトタイプ宣言
***************************************/
class PlayerBullet : public BaseObserver
{
public:
	PlayerBullet();							//コンストラクタ
	~PlayerBullet();						//デストラクタ

	void Init(LineTrailModel model);		//初期化処理
	void Uninit();							//終了処理
	void Update();							//更新処理
	void Draw();							//描画処理

	void OnNotified();
	bool active;

private:
	D3DXVECTOR3 pos;
	TrailCollider *collider;
	LPDIRECT3DVERTEXBUFFER9 vtxBuff;
	int cntFrame;
	D3DXVECTOR3 vtxUp;

	void SetEdgePos(LineTrailModel model);

	static int instanceCount;
	static LPDIRECT3DTEXTURE9 texture;
};

#endif