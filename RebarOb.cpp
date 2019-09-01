//=============================================================================
//
// モデル処理 [player.cpp]
// Author : 自分の氏名
//
//	複数キャラクタ対応版
//
//=============================================================================
#include "RebarOb.h"
#include "Framework\ResourceManager.h"
#include "Framework\Vector3.h"

/**************************************
マクロ定義
***************************************/


/**************************************
コンストラクタ
***************************************/
RebarObstacle::RebarObstacle(const D3DXVECTOR3& pos, LineTrailModel& model, const Transform& player) :
	player(player)
{
	//インスタンス作成
	transform = new Transform();
	collider = new BoxCollider3D(BoxCollider3DTag::Rebar, &transform->pos);

	//コライダー初期化
	const float colliderSize = 10.0f;
	collider->SetSize(D3DXVECTOR3(colliderSize, colliderSize, colliderSize));
	collider->active = true;

	//メッシュ取得
	ResourceManager::Instance()->GetMesh("RebarObstacle", mesh);

	//トランスフォーム初期化
	transform->pos = pos;

	D3DXVECTOR3 right, left;
	model.GetEdgePos(&right, &left);
	D3DXVECTOR3 diff = right - left;
	float angle = Vector3::Angle(Vector3::Right, diff);
	D3DXVECTOR3 axis = Vector3::Axis(Vector3::Right, diff);
	transform->RotateByAxis(angle, axis);

	////回転軸決定
	rotateAxis = Vector3::Axis(Vector3::Forward, diff);

	//フラグ初期化
	isDestroyed = false;
	inMoving = false;
	reserveDestroy = false;
}

/**************************************
デストラクタ
***************************************/
RebarObstacle::~RebarObstacle()
{
	SAFE_DELETE(transform);
	SAFE_DELETE(collider);

	mesh = NULL;
}

/**************************************
更新処理
***************************************/
void RebarObstacle::Update()
{

	if (cntFrame == delay)
	{
		inMoving = true;
		if (reserveDestroy)
		{
			D3DXVECTOR3 noise = D3DXVECTOR3(RandomRangef(-20.0f, 20.0f), RandomRangef(-20.0f, 20.0f), RandomRangef(-20.0f, 20.0f));
			D3DXVECTOR3 diff = player.pos + noise - transform->pos;
			D3DXVec3Normalize(&diff, &diff);
			endPos = transform->pos + diff * moveLength;
		}
	}

	cntFrame++;

	//移動処理
	_Move();

	//回転処理
	transform->RotateByAxis(5.0f, rotateAxis);
}

/**************************************
描画処理
***************************************/
void RebarObstacle::Draw()
{
	transform->SetWorld();
	mesh->Draw();

	BoxCollider3D::DrawCollider(collider);
}

/**************************************
移動処理
***************************************/
void RebarObstacle::Move(const D3DXVECTOR3& offset, int duration, EaseType type)
{
	startPos = transform->pos;
	endPos = transform->pos + offset;
	moveDuration = duration;
	cntFrame = 0;
	moveEaseType = type;
	inMoving = true;
	delay = 0;
}

/**************************************
移動内部処理
***************************************/
void RebarObstacle::_Move()
{
	if (!inMoving)
		return;

	float t = (float)(cntFrame - delay) / moveDuration;
	transform->pos = Easing::EaseValue(t, startPos, endPos, moveEaseType);

	if (cntFrame == moveDuration)
	{
		inMoving = false;

		if (reserveDestroy)
			isDestroyed = true;
	}
}

/**************************************
撃破判定
***************************************/
bool RebarObstacle::IsDestroyed()
{
	return isDestroyed;
}

/**************************************
Move処理
***************************************/
void RebarObstacle::Move(float length, int duration, EaseType type, int delay)
{
	startPos = transform->pos;
	moveLength = length;
	moveDuration = duration;
	cntFrame = 0;
	moveEaseType = type;
	inMoving = false;
	reserveDestroy = true;
	this->delay = delay;
}