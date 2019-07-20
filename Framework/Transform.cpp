//=====================================
//
//トランスフォーム処理[Transform.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "Transform.h"

/**************************************
コンストラクタ
***************************************/
Transform::Transform()
{
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

/**************************************
コンストラクタ
***************************************/
Transform::Transform(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale)
{
	this->pos = pos;
	this->rot = rot;
	this->scale = scale;
}

/**************************************
回転処理
***************************************/
void Transform::Rotate(float degX, float degY, float degZ)
{
	rot.x += D3DXToRadian(degX);
	rot.y += D3DXToRadian(degY);
	rot.z += D3DXToRadian(degZ);
}

/**************************************
ワールド変換行列計算
***************************************/
void Transform::CalcWorldMtx(D3DXMATRIX* out)
{
	D3DXMATRIX rotation, scaling, translation;

	//初期化
	D3DXMatrixIdentity(out);

	//スケーリング
	D3DXMatrixScaling(&scaling, scale.x, scale.y, scale.z);
	D3DXMatrixMultiply(out, out, &scaling);

	//回転
	D3DXMatrixRotationYawPitchRoll(&rotation, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(out, out, &rotation);

	//移動
	D3DXMatrixTranslation(&translation, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(out, out, &translation);
}