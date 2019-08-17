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
RebarObstacle::RebarObstacle(const D3DXVECTOR3& pos, LineTrailModel& model)
{
	//インスタンス作成
	transform = new Transform();
	collider = new TrailCollider(TrailColliderTag::EnemyBullet);

	//コライダー初期化
	collider->SetTrailIndex(model);
	collider->SetAddressZ(&transform->pos.z);
	collider->active = true;

	//メッシュ取得
	ResourceManager::Instance()->GetMesh("RebarObstacle", &mesh);

	//トランスフォーム初期化
	transform->pos = pos;

	D3DXVECTOR3 right, left;
	model.GetEdgePos(&right, &left);
	float angle = Vector3::Angle(Vector3::Right, right - left);
	D3DXVECTOR3 axis = Vector3::Axis(Vector3::Right, right - left);
	transform->RotateByAxis(angle, axis);

	////回転軸決定
	rotateAxis = Vector3::Axis(Vector3::Forward, right - left);

	//フラグ初期化
	isDestroyed = false;
	inMoving = false;
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

	TrailCollider::DrawCollider(collider);
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
}

/**************************************
移動内部処理
***************************************/
void RebarObstacle::_Move()
{
	if (!inMoving)
		return;

	cntFrame++;

	float t = (float)cntFrame / moveDuration;
	transform->pos = Easing::EaseValue(t, startPos, endPos, moveEaseType);

	if (cntFrame == moveDuration)
	{
		inMoving = false;
	}
}

/**************************************
撃破判定
***************************************/
bool RebarObstacle::IsDestroyed()
{
	return isDestroyed;
}