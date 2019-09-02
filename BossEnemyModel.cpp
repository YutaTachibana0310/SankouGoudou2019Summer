//=====================================
//
//ボスエネミーモデル処理[BossEnemyModel.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "BossEnemyModel.h"
#include "BossEnemyActor.h"
#include "BossInit.h"
#include "BossRebarAttack.h"
#include "BossHomingAttack.h"
#include "BossDamageable.h"
#include "BossLargeDamage.h"
#include "BossDefeat.h"
#include "BossIdle.h"
#include "BossUIManager.h"

#include "EnemyBulletController.h"

#include "Framework\ResourceManager.h"
#include "GameParticleManager.h"

#include <random>
#include <algorithm>

using namespace std;
/**************************************
マクロ定義
***************************************/

/**************************************
コンストラクタ
***************************************/
BossEnemyModel::BossEnemyModel(const Transform& player, BossUImanager& uiManager) :
	player(player),
	isDestroyed(false),
	uiManager(uiManager),
	flgBomberHit(false)
{
	actor = new BossEnemyActor();
	bulletController = new EnemyBulletController();
	colliderController = new BossColliderController(*this);

	//ステートマシン作成
	fsm[State::Init] = new BossInit();
	fsm[State::RebarAttack] = new BossRebarAttack();
	fsm[State::HomingAttack] = new BossHomingAttack();
	fsm[State::Damageable] = new BossDamageable();
	fsm[State::LargeDamage] = new BossLargeDamage();
	fsm[State::Defeat] = new BossDefeat;
	fsm[State::Idle] = new BossIdle();

 	//鉄筋のモデルをロード
	ResourceManager::Instance()->LoadMesh("RebarObstacle", "data/MODEL/rebar.x");

	//レベル初期化
	level = 0;

	//Initステートへ遷移
	ChangeState(State::Init);
 }

/**************************************
デストラクタ
***************************************/
BossEnemyModel::~BossEnemyModel()
{
	SAFE_DELETE(actor);
	SAFE_DELETE(bulletController);

	for (auto&& pair : fsm)
	{
		SAFE_DELETE(pair.second);
	}
	fsm.clear();

	
	for (auto&& rebar : rebarList)
	{
		rebar.reset();
	}
	rebarList.clear();
}

/**************************************
更新処理
***************************************/
int BossEnemyModel::Update()
{
	if (flgBomberHit)
	{
		ChangeState(State::LargeDamage);
		flgBomberHit = false;
	}

	int nextState = state->OnUpdate(this);
	if (nextState != currentState)
	{
		ChangeState((State)nextState);
	}

	for (auto&& rebar : rebarList)
	{
		rebar->Update();
	}

	actor->Update();


	bulletController->Update();

	colliderController->Update();

	rebarList.remove_if([](auto&& rebar)
	{
		return rebar->IsDestroyed();
	});

	return 0;
}

/**************************************
描画処理
***************************************/
void BossEnemyModel::Draw()
{
	for (auto&& rebar : rebarList)
	{
		rebar->Draw();
	}

	actor->Draw();

	bulletController->Draw();

	colliderController->Draw();
}

/**************************************
状態遷移処理
***************************************/
void BossEnemyModel::ChangeState(State next)
{
	prevState = currentState;
	currentState = next;
	cntAttack = 0;

	state = fsm[next];
	state->OnStart(this);
}

/**************************************
鉄筋セット処理
***************************************/
void BossEnemyModel::SetRebar(int num)
{
	float z = 300.0f;
	for (int i = 0; i < num; i++)
	{
		int start = Math::RandomRange(0, 5);
		int end = Math::WrapAround(0, 5, start + Math::RandomRange(1, 4));

		LineTrailModel model = LineTrailModel(start, end);
		D3DXVECTOR3 right, left;
		model.GetEdgePos(&right, &left);

		D3DXVECTOR3 pos = right + (left - right) / 2.0f;
		pos.z = z;
		pos.y -= 500.0f;

		std::shared_ptr<RebarObstacle> rebar = std::make_shared<RebarObstacle>(pos, model, player);
		rebar->Move(D3DXVECTOR3(0.0f, 500.0f, 0.0f), 120, EaseType::OutCubic);

		rebarList.push_back(rebar);

		z += 100.0f;
	}
}

/**************************************
鉄筋投擲処理
***************************************/
void BossEnemyModel::ThrowRebar()
{
	const int DelayDelta = 20;
	int delay = 0;
	for (auto&& rebar : rebarList)
	{
		rebar->Move(2500.0f, 180, EaseType::InSine, delay);
		delay += DelayDelta;
	}
}

/**************************************
チャージ開始処理
***************************************/
void BossEnemyModel::StartBulletCharge()
{
	D3DXVECTOR3 SetPos = D3DXVECTOR3(0.0f, 0.0f, 500.0f);

	GameParticleManager::Instance()->SetBossCharge(&SetPos);
}

/**************************************
バレット通知
***************************************/
void BossEnemyModel::NotifyBullet()
{
	const int EdgeMax[Const::LevelMax] = { 3, 3, 4 };
	
	std::vector<int> edgeList;
	MakeOneStrokeEdge(EdgeMax[level], edgeList);

	bulletReserve.clear();
	for (UINT i = 0; i < edgeList.size() - 1; i++)
	{
		LineTrailModel model = LineTrailModel(edgeList[i], edgeList[i + 1]);
		bulletReserve.push_back(model);
		uiManager.SetBulletGuide(model);
	}
}

/**************************************
バレット発射処理
**************************************/
void BossEnemyModel::FireBullet()
{
	static std::vector<D3DXVECTOR3> Emitter = { D3DXVECTOR3(0.0f, 0.0f, 500.0f),  D3DXVECTOR3(0.0f, 0.0f, 500.0f), D3DXVECTOR3(0.0f, 0.0f, 500.0f) };

	for (auto&& model : bulletReserve)
	{
		bulletController->Set(Emitter, model, 60, D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	}
	bulletReserve.clear();
}

/**************************************
コライダーセット処理
**************************************/
void BossEnemyModel::SetCollider()
{
	const int EdgeMax[Const::LevelMax] = {4, 5, 6};
	vector<int> edgeList;

	MakeOneStrokeEdge(EdgeMax[level], edgeList);

	colliderController->SetCollider(edgeList);
}

/**************************************
ダメージ処理
**************************************/
void BossEnemyModel::OnDamage()
{
	actor->ChangeAnimation(BossEnemyActor::AnimID::Damage);
}

/**************************************
爆発処理
**************************************/
void BossEnemyModel::Explode()
{
	actor->SetActive(false);
	D3DXVECTOR3 actorPos = actor->GetActorPosition();
	GameParticleManager::Instance()->SetBossExplosion(&actorPos);
}

/**************************************
爆発チャージ処理
**************************************/
void BossEnemyModel::ChargeExplode(Transform*& charge, Transform*& core)
{
	D3DXVECTOR3 actorPos = actor->GetActorPosition();
	BaseEmitter* emitter = GameParticleManager::Instance()->SetBossExplosionCharge(&actorPos);
	charge = &emitter->transform;

	emitter = GameParticleManager::Instance()->SetBossExplosionCore(&actorPos);
	core = &emitter->transform;

	actor->SetWriteableZ(false);
}

/**************************************
撃墜判定
**************************************/
bool BossEnemyModel::IsDesteoyed()
{
	return isDestroyed;
}

/**************************************
ボンバー着弾処理
**************************************/
void BossEnemyModel::OnHitBomber()
{
	flgBomberHit = true;
}

/**************************************
座標取得処理
**************************************/
D3DXVECTOR3 BossEnemyModel::GetPosition()
{
	return actor->GetActorPosition();
}

/**************************************
一筆書きの軌跡作成処理
**************************************/
void BossEnemyModel::MakeOneStrokeEdge(int edgeNum, std::vector<int>& edgeList)
{
	int prevStart = 5;
	int prevEnd = RandomRange(0, 5);

	edgeList.clear();
	edgeList.reserve(edgeNum);

	vector<int> numberList = { 0, 1, 2, 3, 4 };
	random_device randDevice;
	mt19937_64 getRandMt(randDevice());
	shuffle(numberList.begin(), numberList.end(), getRandMt);

	for (int i = 0; i < edgeNum; i++)
	{
		edgeList.push_back(numberList[Clamp(0, numberList.size(), i)]);
	}
}
