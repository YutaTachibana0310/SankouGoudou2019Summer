//=====================================
//
//プレイヤーバレットヘッダ[PlayerBullet.h]
//Author:GP12B332 21 立花
//
//=====================================
#ifndef _PLAYERBULLET_H_
#define _PLAYERBULLET_H_

#include "main.h"
#include "TrailCollider.h"

/**************************************
マクロ定義
***************************************/

/**************************************
構造体定義
***************************************/

/**************************************
プロトタイプ宣言
***************************************/
class PlayerBullet
{
public:
	PlayerBullet();		//コンストラクタ
	~PlayerBullet();	//デストラクタ

	void Init();		//初期化処理
	void Uninit();		//終了処理
	void Update();		//更新処理
	void Draw();		//描画処理

	void SetTrailIndex(TrailIndex start, TrailIndex end);		//トレイルインデックスセット処理
	void SetEdgePos(D3DXVECTOR3 *left, D3DXVECTOR3 *right);	//端点設定処理
	TrailCollider GetCollider();	//当たり判定取得処理
	bool IsActive();				//アクティブ判定
	bool active;

private:
	D3DXVECTOR3 pos;
	TrailCollider collider;
	LPDIRECT3DVERTEXBUFFER9 vtxBuff;
	int cntFrame;
	D3DXVECTOR3 vtxUp;

	static int instanceCount;
	static LPDIRECT3DTEXTURE9 texture;
};

#endif