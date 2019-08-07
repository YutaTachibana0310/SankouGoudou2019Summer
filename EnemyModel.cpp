//=====================================
//
//ベースエネミーモデル処理[EnemyModel.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "EnemyModel.h"
#include "GameParticleManager.h"
#include "ScoreManager.h"
#include "Framework\BaseEmitter.h"

using namespace std;

/**************************************
マクロ定義
***************************************/

/**************************************
static変数
***************************************/
//五角形の外周を構成するLineModel
const vector<LineTrailModel> EnemyModel::OuterLineModel = {
	LineTrailModel(0, 1),
	LineTrailModel(1, 2),
	LineTrailModel(2, 3),
	LineTrailModel(3, 4),
	LineTrailModel(4, 0)
};


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

	for (auto& enemy : enemyList)
	{
		SAFE_DELETE(enemy);
	}
	enemyList.clear();
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
描画処理
***************************************/
void EnemyModel::Draw()
{
	for (auto& enemy : enemyList)
	{
		enemy->VDraw();
	}

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
	for (auto& enemy : enemyList)
	{
		enemy->VUninit();
		GameParticleManager::Instance()->SetEnemyExplosion(&enemy->m_Pos);

		//スコア・コンボ加算
		SetAddScore(100);
		SetAddCombo(1);
	}

	//チャージエフェクト非表示
	for (auto& emitter : chageEffectList)
	{
		if(emitter != NULL)
			emitter->active = false;
	}

	//非アクティブに
	Uninit();
}

/**************************************
エネミー座標取得処理
***************************************/
void EnemyModel::GetEnemyPosition(vector<D3DXVECTOR3>& out)
{
	for (auto& enemy : enemyList)
	{
		out.push_back(enemy->m_Pos);
	}
}