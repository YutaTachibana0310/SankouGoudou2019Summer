//=====================================
//
//トランスフォームヘッダ[Transform.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "../main.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class Transform
{
public:
	D3DXVECTOR3 pos;	//座標
	D3DXVECTOR3 rot;	//回転
	D3DXVECTOR3 scale;	//スケール

	//コンストラクタ
	Transform();
	Transform(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale);

	//回転処理
	void Rotate(float degX, float degY, float degZ);

	//ワールド変換行列計算処理
	void CalcWorldMtx(D3DXMATRIX* out);
};

#endif