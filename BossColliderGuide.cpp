//=====================================
//
//ボスコライダーガイド処理[BossColliderGuide.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "BossColliderGuide.h"
#include "Framework\ResourceManager.h"
#include "Framework\Vector3.h"

/**************************************
マクロ定義
***************************************/

/**************************************
BossColliderGuideコンストラクタ
***************************************/
BossColliderGuide::BossColliderGuide(LineTrailModel& model)
{
	D3DXVECTOR3 posR, posL;
	model.GetEdgePos(&posR, &posL);

	edgeR = new BossColliderEdge(posR);
	edgeL = new BossColliderEdge(posL);

	line = new BossColliderLine(posR, posL);
}

/**************************************
BossColliderGuideデストラクタ
***************************************/
BossColliderGuide::~BossColliderGuide()
{
	SAFE_DELETE(edgeR);
	SAFE_DELETE(edgeL);

	SAFE_DELETE(line);
}

/**************************************
BossColliderGuide更新処理
***************************************/
void BossColliderGuide::Update()
{
	edgeL->Update();
	edgeR->Update();
}

/**************************************
BossColliderGuide描画処理
***************************************/
void BossColliderGuide::Draw()
{
	line->Draw();
	edgeL->Draw();
	edgeR->Draw();
}

/**************************************
BossColliderGuideLineコンストラクタ
***************************************/
BossColliderLine::BossColliderLine(const D3DXVECTOR3& edgeR, const D3DXVECTOR3& edgeL)
{
	ResourceManager::Instance()->GetPolygon("BossColliderLine", &polygon);

	D3DXVECTOR3 diff = edgeL - edgeR;

	transform = new Transform();
	transform->pos = edgeR + diff / 2.0f;
	transform->pos.z = 500.0f;

	transform->scale.x = Vector3::Distance(edgeL, edgeR);

	float angle = Vector3::Angle(Vector3::Right, diff);
	D3DXVECTOR3 axis = Vector3::Axis(Vector3::Right, diff);
	transform->RotateByAxis(angle, axis);
}

/**************************************
BossColliderGuideLineデストラクタ
***************************************/
BossColliderLine::~BossColliderLine()
{
	polygon = NULL;
	SAFE_DELETE(transform);
}

/**************************************
BossColliderGuideLine描画処理
***************************************/
void BossColliderLine::Draw()
{
	transform->SetWorld();
	polygon->Draw();
}

/**************************************
BossColliderGuideEdgeコンストラクタ
***************************************/
BossColliderEdge::BossColliderEdge(const D3DXVECTOR3& pos)
{
	ResourceManager::Instance()->GetPolygon("BossColliderEdge", &polygon);

	transform = new Transform();
	transform->pos = pos;
	transform->pos.z = 500.0f;
}

/**************************************
BossColliderGuideEdgeデストラクタ
***************************************/
BossColliderEdge::BossColliderEdge()
{
	polygon = NULL;
	SAFE_DELETE(transform);
}

/**************************************
BossColliderGuideEdge更新処理
***************************************/
void BossColliderEdge::Update()
{
	transform->Rotate(0.0f, 0.0f, 5.0f);
}

/**************************************
BossColliderGuideEdge描画処理
***************************************/
void BossColliderEdge::Draw()
{
	transform->SetWorld();
	polygon->Draw();
}
