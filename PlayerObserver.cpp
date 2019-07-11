//=====================================
//
//プレイヤーオブザーバー処理[PlayerObserver.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "PlayerObserver.h"
#include "InputController.h"

#include "PlayerMove.h"
#include "PlayerWait.h"
#include "PlayerReturn.h"
#include "PlayerIdle.h"

#include <algorithm>

using namespace std;

/**************************************
マクロ定義
***************************************/
#define MOVETARGET_DEFAULT	(99)

/**************************************
構造体定義
***************************************/



/**************************************
コンストラクタ
***************************************/
PlayerObserver::PlayerObserver()
{
	player = new Player();
	model = new PlayerModel();
	trailEffect = new PlayerTrail();
	bomberController = new PlayerBomberController();
	bulletController = new PlayerBulletController();

	fsm[PlayerState::Idle] = new PlayerIdle();
	fsm[PlayerState::Wait] = new PlayerWait();
	fsm[PlayerState::Move] = new PlayerMove();
	fsm[PlayerState::Return] = new PlayerReturn();

	//移動先確保
	targetPos.resize(5);
	for (UINT i = 0; i < targetPos.size(); i++)
	{
		targetPos[i] = LineTrailModel::GetEdgePos(i);
	}

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

	SAFE_DELETE(bomberController);
	SAFE_DELETE(bulletController);

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
	ChangeStatePlayer(PlayerState::Idle);
}

/**************************************
終了処理
***************************************/
void PlayerObserver::Uninit()
{
	player->Uninit();

	bomberController->Uninit();
	bulletController->Uninit();
}

/**************************************
更新処理
***************************************/
void PlayerObserver::Update()
{
	int stateResult = player->Update();

	if (stateResult != STATE_CONTINUOUS)
		OnPlayerStateFinish();

	bulletController->Update();

	trailEffect->Update();

	bomberController->Update();
}

/**************************************
描画処理
***************************************/
void PlayerObserver::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	player->Draw();

	trailEffect->Draw();
	
	bomberController->Draw();
	bulletController->Draw();
}

/**************************************
入力確認処理
***************************************/
void PlayerObserver::CheckInput()
{
	//入力間隔をカウント
	player->inputInterval++;

	//入力を確認
	for (int i = 0; i < INPUTBUTTON_MAX; i++)
	{
		if (!IsEntered(i))
			continue;

		PushInput(i);
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

	//プレイヤーの入力間隔をリセット
	player->inputInterval = 0;

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
		LineTrailModel modelTrail;
		model->GetPlayerTrail(&modelTrail);
		bulletController->SetPlayerBullet(modelTrail);
	}

	//一筆書き判定
	if (model->CheckOneStroke())
	{

		//ボム発射
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