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

#include "EnemyBulletController.h"

#include "Framework\ResourceManager.h"
#include "GameParticleManager.h"

using namespace std;
/**************************************
マクロ定義
***************************************/

/**************************************
コンストラクタ
***************************************/
BossEnemyModel::BossEnemyModel()
{
	actor = new BossEnemyActor();
	bulletController = new EnemyBulletController();
	colliderController = new BossColliderController();

	//ステートマシン作成
	fsm[State::Init] = new BossInit();
	fsm[State::RebarAttack] = new BossRebarAttack();
	fsm[State::HomingAttack] = new BossHomingAttack();
	fsm[State::Damageable] = new BossDamageable();

	//鉄筋のモデルをロード
	ResourceManager::Instance()->LoadMesh("RebarObstacle", "data/MODEL/rebar.x");

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
}

/**************************************
更新処理
***************************************/
int BossEnemyModel::Update()
{
	updateResult = StateContinuous;

	state->OnUpdate(this);

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
	state = fsm[next];
	state->OnStart(this);

	prevState = currentState;
	currentState = next;
	cntAttack = 0;
}

/**************************************
鉄筋セット処理
***************************************/
void BossEnemyModel::SetRebar()
{
	float z = 300.0f;
	//for (int i = 0; i < 5; i++)
	{
		int start = Math::RandomRange(0, 5);
		int end = Math::WrapAround(0, 5, start + Math::RandomRange(1, 4));

		LineTrailModel model = LineTrailModel(start, end);
		D3DXVECTOR3 right, left;
		model.GetEdgePos(&right, &left);

		D3DXVECTOR3 pos = right + (left - right) / 2.0f;
		pos.z = z;
		pos.y -= 500.0f;

		RebarObstacle *rebar = new RebarObstacle(pos, model);
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
	for (auto&& rebar : rebarList)
	{
		rebar->Move(D3DXVECTOR3(0.0f, 0.0f, -2000.0f), 300, EaseType::InOutCubic);
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
バレット発射処理
**************************************/
void BossEnemyModel::FireBullet()
{
	static std::vector<D3DXVECTOR3> Emitter = { D3DXVECTOR3(0.0f, 0.0f, 500.0f),  D3DXVECTOR3(0.0f, 0.0f, 500.0f), D3DXVECTOR3(0.0f, 0.0f, 500.0f) };

	bulletController->Set(Emitter, LineTrailModel(0, 1), 60, D3DXVECTOR3(2.0f, 2.0f, 2.0f));
}

/**************************************
コライダーセット処理
**************************************/
void BossEnemyModel::SetCollider()
{
	const UINT EdgeMax = 3;
	int prevStart = 5;
	int prevEnd = RandomRange(0, 5);

	std::vector<int> edgeList;
	edgeList.reserve(EdgeMax);

	for (UINT i = 0; i < EdgeMax; i++)
	{
		int start = prevEnd;
		edgeList.push_back(start);

		int end = prevStart;
		while (end == prevStart)
		{
			end = WrapAround(0, 5, start + RandomRange(1, 5));
		}
		prevEnd = end;
	}

	colliderController->SetCollider(edgeList);
}