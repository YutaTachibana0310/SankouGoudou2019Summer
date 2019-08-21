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

/**************************************
コンストラクタ
***************************************/
BossEnemyActor::BossEnemyActor()
{
	animManager = new AnimationManager();

	//モデルファイル読み込み
	const char* ModelFileName = "data/MODEL/Boss.x";
	animManager->LoadXFile(ModelFileName, "Boss");

	//アニメーション読み込み
	const char* AnimationSetName[] = {
		"Flying", "Attack01", "Attack02", "Damage", "Death", "Idle", "LargeDamage"
	};
	for (UINT i = 0; i < AnimID::Max; i++)
	{
		animManager->LoadAnimation(AnimationSetName[i], i, 0.3f);
	}

	//アニメーションスピード設定
	const float AnimationPlaySpeed[] = {
		1.0f, 0.6f, 0.6f, 1.5f, 1.0f, 1.0f, 1.5f
	};
	for (UINT i = 0; i < AnimID::Max; i++)
	{
		animManager->SetPlaySpeed(i, AnimationPlaySpeed[i]);
	}

	//遷移関係設定
	animManager->SetFinishTransition(AnimID::Attack01, AnimID::Idle);
	animManager->SetFinishTransition(AnimID::Attack02, AnimID::Idle);
	animManager->SetFinishTransition(AnimID::Damage, AnimID::Idle);
	animManager->SetFinishTransition(AnimID::LargeDamage, AnimID::Idle);

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
	transform.pos = Easing::EaseValue(t, prevPos, targetPos, EaseType::OutBack);

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