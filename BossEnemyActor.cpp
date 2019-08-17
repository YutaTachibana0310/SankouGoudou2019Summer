//=====================================
//
//ボスエネミーアクター処理[BossEnemyActor.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "BossEnemyActor.h"
#include "Framework\AnimationManager.h"
#include "Framework\Easing.h"
#include "Framework\Vector3.h"

/**************************************
マクロ定義
***************************************/
static const char* AnimationSetName[] = {
	"Attack01", "Attack02", "Damage", "Death", "Flying", "Idle"
};

static const char* ModelFileName = "data/MODEL/Boss.x";

/**************************************
コンストラクタ
***************************************/
BossEnemyActor::BossEnemyActor()
{
	animManager = new AnimationManager();

	//モデルファイル読み込み
	animManager->LoadXFile(ModelFileName, "Boss");

	//アニメーション読み込み
	for (UINT i = 0; i < AnimID::Max; i++)
	{
		animManager->LoadAnimation(AnimationSetName[i], i);
	}

	//遷移関係設定
	animManager->SetFinishTransition(AnimID::Attack01, AnimID::Idle);
	animManager->SetFinishTransition(AnimID::Attack02, AnimID::Idle);
	animManager->SetFinishTransition(AnimID::Damage, AnimID::Idle);
	
	//フラグ初期化
	inMoving = false;
	inRotaiton = false;

	transform.scale = 50.0f * D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

/**************************************
デストラクタ
***************************************/
BossEnemyActor::~BossEnemyActor()
{
	SAFE_DELETE(animManager);
}

/**************************************
更新処理
***************************************/
void BossEnemyActor::Update()
{
	_Move();
	
	_Rotate();

	animManager->Update();
}

/**************************************
描画処理
***************************************/
void BossEnemyActor::Draw()
{
	transform.SetWorld();

	D3DXMATRIX world = transform.GetMatrix();
	animManager->Draw(&world);
}

/**************************************
移動処理
***************************************/
void BossEnemyActor::Move(const D3DXVECTOR3& target, int duration)
{
	if (inMoving)
		return;

	targetPos = target;
	prevPos = transform.pos;
	cntMove = 0;
	durationMove = duration;
	inMoving = true;
}

/**************************************
回転処理
***************************************/
void BossEnemyActor::Rotate(const D3DXVECTOR3& target, float magnitude)
{
	if (inRotaiton)
		return;

	targetForward = target;
	magnitudeRotate = magnitude;
	inRotaiton = true;
}

/**************************************
アニメーション変更処理
***************************************/
void BossEnemyActor::ChangeAnimation(AnimID next)
{
	animManager->ChangeAnim(next, true);
}

/**************************************
移動処理（内部）
***************************************/
void BossEnemyActor::_Move()
{
	if (!inMoving)
		return;

	cntMove++;

	float t = (float)cntMove / durationMove;
	transform.pos = Easing::EaseValue(t, prevPos, targetPos, EaseType::OutCirc);

	if (cntMove == durationMove)
		inMoving = false;
}

/**************************************
回転処理（内部）
***************************************/
void BossEnemyActor::_Rotate()
{
	if (!inRotaiton)
		return;

	float angle = Vector3::Angle(transform.Forward(), targetForward);
	D3DXVECTOR3 axis = Vector3::Axis(transform.Forward(), targetForward);
	transform.RotateByAxis(angle * magnitudeRotate, axis);

	if (angle < 0.01f)
		inRotaiton = false;
}