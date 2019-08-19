//=====================================
//
//�{�X�R���C�_�[�K�C�h����[BossColliderGuide.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "BossColliderGuide.h"
#include "Framework\ResourceManager.h"
#include "Framework\Vector3.h"

/**************************************
�}�N����`
***************************************/

/**************************************
BossColliderGuide�R���X�g���N�^
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
BossColliderGuide�f�X�g���N�^
***************************************/
BossColliderGuide::~BossColliderGuide()
{
	SAFE_DELETE(edgeR);
	SAFE_DELETE(edgeL);

	SAFE_DELETE(line);
}

/**************************************
BossColliderGuide�X�V����
***************************************/
void BossColliderGuide::Update()
{
	edgeL->Update();
	edgeR->Update();
}

/**************************************
BossColliderGuide�`�揈��
***************************************/
void BossColliderGuide::Draw()
{
	line->Draw();
	edgeL->Draw();
	edgeR->Draw();
}

/**************************************
BossColliderGuideLine�R���X�g���N�^
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
BossColliderGuideLine�f�X�g���N�^
***************************************/
BossColliderLine::~BossColliderLine()
{
	polygon = NULL;
	SAFE_DELETE(transform);
}

/**************************************
BossColliderGuideLine�`�揈��
***************************************/
void BossColliderLine::Draw()
{
	transform->SetWorld();
	polygon->Draw();
}

/**************************************
BossColliderGuideEdge�R���X�g���N�^
***************************************/
BossColliderEdge::BossColliderEdge(const D3DXVECTOR3& pos)
{
	ResourceManager::Instance()->GetPolygon("BossColliderEdge", &polygon);

	transform = new Transform();
	transform->pos = pos;
	transform->pos.z = 500.0f;
}

/**************************************
BossColliderGuideEdge�f�X�g���N�^
***************************************/
BossColliderEdge::BossColliderEdge()
{
	polygon = NULL;
	SAFE_DELETE(transform);
}

/**************************************
BossColliderGuideEdge�X�V����
***************************************/
void BossColliderEdge::Update()
{
	transform->Rotate(0.0f, 0.0f, 5.0f);
}

/**************************************
BossColliderGuideEdge�`�揈��
***************************************/
void BossColliderEdge::Draw()
{
	transform->SetWorld();
	polygon->Draw();
}
