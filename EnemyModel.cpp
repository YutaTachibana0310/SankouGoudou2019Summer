//=====================================
//
//ベースエネミーモデル処理[EnemyModel.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "EnemyModel.h"

/**************************************
マクロ定義
***************************************/

/**************************************
構造体定義
***************************************/

/**************************************
コンストラクタ
***************************************/
EnemyModel::EnemyModel()
{
	collider = new TrailCollider(TrailColliderTag::Enemy);
	collider->AddObserver(this);
	pos.z = 250.0f;
	collider->SetAddressZ(&pos.z);
	active = false;
}

/**************************************
デストラクタ
***************************************/
EnemyModel::~EnemyModel()
{
	SAFE_DELETE(collider);
}

/**************************************
初期化処理
***************************************/
void EnemyModel::Init(LineTrailModel model)
{
	this->model = model;
	collider->SetTrailIndex(model);
	cntFrame = 0;
	active = true;
}

/**************************************
終了処理
***************************************/
void EnemyModel::Uninit()
{
	collider->active = false;
	active = false;
}

/**************************************
更新処理
***************************************/
int EnemyModel::Update()
{
	return state->OnUpdate(this);
}

/**************************************
描画処理
***************************************/
void EnemyModel::Draw()
{

#ifdef TRAILCOLLIDER_USE_DEBUG
	TrailCollider::DrawCollider(collider);
#endif
}

/**************************************
衝突判定通知レシーバー
***************************************/
void EnemyModel::OnNotified(ObserveSubject *notifier)
{
	//所属するすべてのエネミーにダメージ処理

	//非アクティブに
	Uninit();
}

/**************************************
状態遷移処理
***************************************/
void EnemyModel::ChangeState(IStateMachine<EnemyModel> *next)
{
	state = next;
	state->OnStart(this);
}