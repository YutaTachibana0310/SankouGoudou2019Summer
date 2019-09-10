//=====================================
//
//InputGuide.cpp
//機能:入力ガイド表示
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "InputGuide.h"
#include "LineTrailModel.h"
#include "camera.h"
#include "Framework\Vector3.h"

/**************************************
グローバル変数
***************************************/

/**************************************
コンストラクタ
***************************************/
InputGuide::InputGuide()
{
	LoadTexture("data/TEXTURE/UI/inputGuide.png");
	SetSize(100.0f, 100.0f);
}

/**************************************
描画処理
***************************************/
void InputGuide::Draw()
{
	if (!active)
		return;

	Polygon2D::Draw();
	active = false;
}

/**************************************
セット処理
***************************************/
void InputGuide::Set(LineTrailModel & model)
{
	//モデルから端点のワールド座標
	D3DXVECTOR3 start, end;
	model.GetEdgePos(&start, &end);

	//正規化ラインベクトルを計算
	D3DXVECTOR3 diff = end - start;
	D3DXVec3Normalize(&diff, &diff);

	//ワールド座標をスクリーン座標に変換
	D3DXVECTOR3 worldPos = start + diff * 30.0f;
	Camera::Instance()->Projection(transform.pos, worldPos);

	//回転
	float angle = Vector3::Angle(Vector3::Up, diff);
	D3DXVECTOR3 axis = Vector3::Axis(Vector3::Up, diff);
	transform.IdentifyRotation();
	transform.RotateByAxis(-angle, axis);

	//アクティベイト
	active = true;
}
