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
	D3DXQuaternionIdentity(&rot);
	scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

/**************************************
コンストラクタ
***************************************/
Transform::Transform(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale)
{
	this->pos = pos;
	D3DXQuaternionRotationYawPitchRoll(&this->rot, rot.y, rot.x, rot.z);
	this->scale = scale;
}

/**************************************
回転処理
***************************************/
void Transform::Rotate(float degX, float degY, float degZ)
{
	D3DXQUATERNION q;
	D3DXQuaternionRotationYawPitchRoll(&q, D3DXToRadian(degY), D3DXToRadian(degX), D3DXToRadian(degZ));
	D3DXQuaternionMultiply(&rot, &rot, &q);
}

/***************************************
回転処理
***************************************/
void Transform::RotateByAxis(float deg, D3DXVECTOR3 axis)
{
	D3DXQUATERNION q;
	D3DXQuaternionRotationAxis(&q, &axis, D3DXToRadian(deg));
	D3DXQuaternionMultiply(&rot, &rot, &q);
}

/***************************************
回転初期化処理
***************************************/
void Transform::IdentifyRotation()
{
	D3DXQuaternionIdentity(&rot);
}

/**************************************
ワールド変換処理
***************************************/
void Transform::SetWorld()
{
	D3DXMATRIX world, rotation, scaling, translation;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//初期化
	D3DXMatrixIdentity(&world);

	//スケーリング
	D3DXMatrixScaling(&scaling, scale.x, scale.y, scale.z);
	D3DXMatrixMultiply(&world, &world, &scaling);

	//回転
	D3DXMatrixRotationQuaternion(&rotation, &rot);
	D3DXMatrixMultiply(&world, &world, &rotation);

	//移動
	D3DXMatrixTranslation(&translation, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&world, &world, &translation);

	pDevice->SetTransform(D3DTS_WORLD, &world);
}

/**************************************
ビルボード処理
***************************************/
void Transform::SetWorldInvView()
{
	D3DXMATRIX world, rotation, scaling, translation, view, invView;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//初期化
	D3DXMatrixIdentity(&world);

	//スケーリング
	D3DXMatrixScaling(&scaling, scale.x, scale.y, scale.z);
	D3DXMatrixMultiply(&world, &world, &scaling);

	//回転
	D3DXMatrixRotationQuaternion(&rotation, &rot);
	D3DXMatrixMultiply(&world, &world, &rotation);

	//ビュー逆変換
	pDevice->GetTransform(D3DTS_VIEW, &view);
	D3DXMatrixInverse(&invView, NULL, &view);
	invView._41 = invView._42 = invView._43 = 0.0f;

	//移動
	D3DXMatrixTranslation(&translation, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&world, &world, &translation);

	pDevice->SetTransform(D3DTS_WORLD, &world);
}

/**************************************
前方計算処理
***************************************/
D3DXVECTOR3 Transform::Forward()
{
	D3DXVECTOR3 forward = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	D3DXMATRIX rotation;

	D3DXMatrixRotationQuaternion(&rotation, &rot);
	D3DXVec3TransformCoord(&forward, &forward, &rotation);

	return forward;
}

/**************************************
右方計算処理
***************************************/
D3DXVECTOR3 Transform::Right()
{
	D3DXVECTOR3 right = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	D3DXMATRIX rotation;

	D3DXMatrixRotationQuaternion(&rotation, &rot);
	D3DXVec3TransformCoord(&right, &right, &rotation);

	return right;
}

/**************************************
上方計算処理
***************************************/
D3DXVECTOR3 Transform::Up()
{
	D3DXVECTOR3 up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXMATRIX rotation;

	D3DXMatrixRotationQuaternion(&rotation, &rot);
	D3DXVec3TransformCoord(&up, &up, &rotation);

	return up;
}

/**************************************
ワールド行列取得処理
***************************************/
D3DXMATRIX Transform::GetMatrix()
{
	D3DXMATRIX world, rotation, scaling, translation;

	//初期化
	D3DXMatrixIdentity(&world);

	//スケーリング
	D3DXMatrixScaling(&scaling, scale.x, scale.y, scale.z);
	D3DXMatrixMultiply(&world, &world, &scaling);

	//回転
	D3DXMatrixRotationQuaternion(&rotation, &rot);
	D3DXMatrixMultiply(&world, &world, &rotation);

	//移動
	D3DXMatrixTranslation(&translation, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&world, &world, &translation);

	return world;
}