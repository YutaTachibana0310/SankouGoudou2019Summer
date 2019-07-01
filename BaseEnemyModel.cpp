//=====================================
//
//ベースエネミーモデル処理[BaseEnemyModel.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "BaseEnemyModel.h"

/**************************************
マクロ定義
***************************************/

/**************************************
構造体定義
***************************************/

/**************************************
コンストラクタ
***************************************/
BaseEnemyModel::BaseEnemyModel()
{
	collider = new TrailCollider(TrailColliderTag::Enemy);
	collider->AddObserver(this);
	pos.z = 500.0f;
	collider->SetAddressZ(&pos.z);
	active = false;
}

/**************************************
デストラクタ
***************************************/
BaseEnemyModel::~BaseEnemyModel()
{
	SAFE_DELETE(collider);
}

/**************************************
初期化処理
***************************************/
void BaseEnemyModel::Init(LineTrailModel model)
{
	this->model = model;
	collider->SetTrailIndex(model);
	cntFrame = 0;
	active = true;
}

/**************************************
終了処理
***************************************/
void BaseEnemyModel::Uninit()
{
	collider->RemoveFromCheckList();
	active = false;
}

/**************************************
更新処理
***************************************/
int BaseEnemyModel::Update()
{
	return state->OnUpdate(this);
}

/**************************************
描画処理
***************************************/
void BaseEnemyModel::Draw()
{

}

/**************************************
衝突判定通知レシーバー
***************************************/
void BaseEnemyModel::OnNotified(ObserveSubject *notifier)
{

}

/**************************************
状態遷移
***************************************/
void BaseEnemyModel::ChangeState(IStateMachine<BaseEnemyModel> *next)
{
	state = next;
	state->OnStart(this);
}