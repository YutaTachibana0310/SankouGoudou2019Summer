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
#include <algorithm>
#include "sound.h"
#include "camera.h"
#include "Framework\CameraShakePlugin.h"

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

//加算スコアの素点
const int EnemyModel::BaseScorePoint = 50;

/**************************************
コンストラクタ
***************************************/
EnemyModel::EnemyModel() :
	explosionScale(1.0f)
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
		enemy.reset();
	}
	enemyList.clear();

	for (auto& emitter : chageEffectList)
	{
		if (emitter != NULL)
			emitter->active = false;
	}
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
		enemy->m_FlgDestroyed = true;
	}

	//チャージエフェクト非表示
	for (auto& emitter : chageEffectList)
	{
		if(emitter != NULL)
			emitter->active = false;
	}
}

/**************************************
撃破済みエネミー確認処理
***************************************/
void EnemyModel::CheckDestroied()
{
	for (auto& enemy : enemyList)
	{
		if (!enemy->m_FlgDestroyed)
			continue;

		enemy->VUninit();
		GameParticleManager::Instance()->SetEnemyExplosion(&enemy->m_Pos, explosionScale);

		//スコア・コンボ加算
		SetAddCombo(1);
		SetAddScore(BaseScorePoint);

		//消滅SE
		Sound::GetInstance()->SetPlaySE(ENEMYDOWN1, true, (Sound::GetInstance()->changevol / 100.0f));

		//カメラ揺らす
		const D3DXVECTOR3 ShakeAmplitude = D3DXVECTOR3(0.75f, 0.75f, 0.0f);
		const int ShakeDuration = 120;
		Camera::ShakePlugin::Instance()->Set(ShakeAmplitude, ShakeDuration);

		enemy.reset();
	}

	//消去
	auto itrNewEnd = remove_if(enemyList.begin(), enemyList.end(), [](auto&& enemy)
	{
		return !enemy;
	});
	enemyList.erase(itrNewEnd, enemyList.end());

	if (enemyList.empty())
	{
		Uninit();
	}
}

/**************************************
エネミー座標取得処理
***************************************/
void EnemyModel::GetShotPos(std::vector<D3DXVECTOR3>& out)
{
	for (auto&& enemy : enemyList)
	{
		out.push_back(enemy->m_Pos + ShotPosOffset);
	}
}

/**************************************
エネミー座標取得処理
***************************************/
void EnemyModel::GetEnemy(list<shared_ptr<Enemy>>& out)
{
	for (auto& enemy : enemyList)
	{
		//Z座標が負なら追加しない
		if (enemy->m_Pos.z < 0.0f)
			continue;

		//エネミーのワールド座標をスクリーン座標へ変換
		D3DXVECTOR3 screenPos;
		Camera::Instance()->Projection(screenPos, enemy->m_Pos);

		//スクリーン外にいたら追加しない
		if (screenPos.x < 0.0f || screenPos.x > SCREEN_WIDTH * 1.0f)
			continue;

		if (screenPos.y < 0.0f || screenPos.z > SCREEN_HEIGHT * 1.0f)
			continue;

		out.push_back(enemy);
	}
}