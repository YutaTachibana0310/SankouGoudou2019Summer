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
	PlayerBullet();
	~PlayerBullet();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void Set(TrailIndex start, TrailIndex end);
	TrailCollider GetCollider();
	bool IsActive();

	//テスト用
	void Set(D3DXVECTOR3 start, D3DXVECTOR3 end);
	D3DXVECTOR3 pos;

private:
	bool active;
	TrailCollider collider;
	LPDIRECT3DVERTEXBUFFER9 vtxBuff;
	LPDIRECT3DTEXTURE9 texture;
};

#endif