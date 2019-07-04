//=====================================
//
//プレイヤーオブザーバー処理[PlayerObserver.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "PlayerObserver.h"

#include "PlayerMove.h"
#include "PlayerWait.h"
#include "PlayerReturn.h"
#include "PlayerIdle.h"
#include "PlayerBomber.h"

#include <algorithm>

using namespace std;

/**************************************
マクロ定義
***************************************/
#define MOVETARGET_DEFAULT	(99)

/**************************************
構造体定義
***************************************/


PlayerBomber *bomber;

/**************************************
コンストラクタ
***************************************/
PlayerObserver::PlayerObserver()
{
	player = new Player();
	model = new PlayerModel();
	trailEffect = new PlayerTrail();
	bomber = new PlayerBomber();

	fsm[PlayerState::Idle] = new PlayerIdle();
	fsm[PlayerState::Wait] = new PlayerWait();
	fsm[PlayerState::Move] = new PlayerMove();
	fsm[PlayerState::Return] = new PlayerReturn();

	//移動先確保
	targetPos.resize(5);

	//moveTarget初期化
	moveTarget = MOVETARGET_DEFAULT;
}

/**************************************
デストラクタ
***************************************/
PlayerObserver::~PlayerObserver()
{
	SAFE_DELETE(player);
	SAFE_DELETE(model);
	SAFE_DELETE(trailEffect);

	for (PlayerBullet* bullet : bulletContainer)
	{
		SAFE_DELETE(bullet);
	}
	bulletContainer.clear();

	for (auto stateMachine : fsm)
	{
		SAFE_DELETE(stateMachine.second);
	}
	fsm.clear();
}

/**************************************
初期化処理
***************************************/
void PlayerObserver::Init()
{
	player->Init();
	for (PlayerBullet *bullet : bulletContainer)
	{
		bullet->Init();

	}


	ChangeStatePlayer(PlayerState::Idle);
}

/**************************************
終了処理
***************************************/
void PlayerObserver::Uninit()
{
	player->Uninit();
	for (PlayerBullet *bullet : bulletContainer)
	{
		bullet->Uninit();
	}
	
	bomber->Uninit();
	
}

/**************************************
更新処理
***************************************/
void PlayerObserver::Update()
{
	int stateResult = player->Update();

	if (stateResult != STATE_CONTINUOUS)
		OnPlayerStateFinish();

	for (PlayerBullet *bullet : bulletContainer)
	{
		bullet->Update();
	}

	if (bomber->active)
	{
		bomber->Update();
	}
	trailEffect->Update();
}

/**************************************
描画処理
***************************************/
void PlayerObserver::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	player->Draw();

	trailEffect->Draw();

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	pDevice->SetRenderState(D3DRS_LIGHTING, false);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

	for (PlayerBullet *bullet : bulletContainer)
	{
		bullet->Draw();
	}
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	pDevice->SetRenderState(D3DRS_LIGHTING, true);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
	
	bomber->Draw();
	
}

/**************************************
バレット発射処理
***************************************/
void PlayerObserver::SetPlayerBullet(PlayerTrailModel trail)
{
	auto itr = find_if(bulletContainer.begin(), bulletContainer.end(), [](PlayerBullet* bullet)
	{
		return !bullet->active;
	});

	if (itr != bulletContainer.end())
	{
		(*itr)->SetTrailIndex((TrailIndex)trail.start, (TrailIndex)trail.end);
		(*itr)->SetEdgePos(&targetPos[trail.start], &targetPos[trail.end]);
		(*itr)->Init();
	}
	else
	{
		PlayerBullet *bullet = new PlayerBullet();
		bullet->SetTrailIndex((TrailIndex)trail.start, (TrailIndex)trail.end);
		bullet->SetEdgePos(&targetPos[trail.start], &targetPos[trail.end]);
		bullet->Init();
		bulletContainer.push_back(bullet);
	}
}

/**************************************
入力処理
***************************************/
void PlayerObserver::PushInput(int num)
{
	//同じところへは移動しない
	if (num == moveTarget)
		return;

	//Wait状態であればMoveに遷移
	if (current == PlayerState::Wait || current == PlayerState::Idle)
	{
		if(current == PlayerState::Wait)
			trailEffect->Init(&player->transform.pos);

		moveTarget = num;
		player->goalpos = targetPos[moveTarget];
		ChangeStatePlayer(PlayerState::Move);
	}
	//先行入力を保存して何もしない
	else
	{
		model->PushInput(num);
	}
}

/**************************************
移動目標設定
***************************************/
void PlayerObserver::SetMoveTargetPosition(int i, D3DXVECTOR3 pos)
{
	targetPos[i] = pos;
}

/**************************************
Player状態遷移
***************************************/
void PlayerObserver::ChangeStatePlayer(PlayerState next)
{
	prevState = current;
	current = next;
	player->ChangeState(fsm[current]);
}

/**************************************
プレイヤーの状態終了時の処理
***************************************/
void PlayerObserver::OnPlayerStateFinish()
{
	switch (current)
	{
	case PlayerState::Move:
		OnFinishPlayerMove();
			break;

	case PlayerState::Wait:
		OnFinishPlayerWait();
		break;

	case PlayerState::Return:
		OnFinishPlayerReturn();
		break;

	}
}
/**************************************
Moveコールバック
***************************************/
void PlayerObserver::OnFinishPlayerMove()
{
	//移動履歴をプッシュ
	model->PushMoveStack(moveTarget);

	//トレイルを終了
	trailEffect->Uninit();

	//WaitかｒMoveからの移動であればバレット発射
	if (prevState == PlayerState::Wait || prevState == PlayerState::Move)
	{
		PlayerTrailModel modelTrail;
		model->GetPlayerTrail(&modelTrail);
		SetPlayerBullet(modelTrail);

	}

	//一筆書き判定
	if (model->CheckOneStroke())
	{
		//ボム発射
		bomber->SetBomber(&player->bompos,player->transform.pos);
	}

	//先行入力確認
	if (model->IsExistPrecedInput(&moveTarget))
	{
		player->goalpos = targetPos[moveTarget];
		trailEffect->Init(&player->transform.pos);
		ChangeStatePlayer(PlayerState::Move);
	}
	//無ければ待機状態へ遷移
	else
	{
		ChangeStatePlayer(PlayerState::Wait);
	}
}

/**************************************
Waitコールバック
***************************************/
void PlayerObserver::OnFinishPlayerWait()
{
	//TODO:初期位置に戻るので色々リセット
	model->Clear();
	moveTarget = MOVETARGET_DEFAULT;

	//Return状態へ遷移し初期位置へ
	ChangeStatePlayer(PlayerState::Return);
}

/**************************************
Returnコールバック
***************************************/
void PlayerObserver::OnFinishPlayerReturn()
{
	//プレイヤーをIdle状態へ遷移
	ChangeStatePlayer(PlayerState::Idle);
}