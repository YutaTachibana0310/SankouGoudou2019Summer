//=====================================
//
//バレットヘッダ[PlayerBullet.h]
//Author:GP12B332 12 権頭
//
//=====================================
#ifndef _PLAYERBULLET_H_
#define _PLAYERBULLET_H_

#include "main.h"

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

	// 変数
	D3DXVECTOR3			pos;				// 現在の位置
	D3DXVECTOR3			move;				// 移動量
	D3DXVECTOR3			scl;				// モデルの大きさ(スケール)
	D3DXVECTOR3			rot;				// 現在の向き
	D3DXVECTOR3			rotDest;			// 目的の向き

	// 関数
	void Init();
	void Uninit();
	void Update();
	void Draw();
};

#endif