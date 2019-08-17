//=====================================
//
//ボスエネミーモデル処理[BossEnemyModel.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "BossEnemyModel.h"
#include "BossEnemyActor.h"
#include "BossInit.h"

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

	//ステートマシン作成
	fsm[State::Init] = new BossInit();

	//Initステートへ遷移
	ChangeState(State::Init);
 }

/**************************************
デストラクタ
***************************************/
BossEnemyModel::~BossEnemyModel()
{
	SAFE_DELETE(actor);
}

/**************************************
更新処理
***************************************/
int BossEnemyModel::Update()
{
	state->OnUpdate(this);

	actor->Update();
	return 0;
}

/**************************************
描画処理
***************************************/
void BossEnemyModel::Draw()
{
	actor->Draw();
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
}