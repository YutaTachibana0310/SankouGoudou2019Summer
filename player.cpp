//=====================================
//
//プレイヤー処理[player.cpp]
//Author:GP12B332 12 権頭
//
//=====================================
#include "player.h"

#include "main.h"
#include "player.h"
#include "PlayerController.h"
#include "GameParticleManager.h"

#include "starUI.h"
#include "debugWindow.h"
#include "PostEffect\SpikeNoiseController.h"

using namespace std;

/**************************************
マクロ定義
***************************************/
#define PLAYER_MODEL				"data/MODEL/airplane000.x"
#define PLAYER_DAMAGE				(10.0f)		//プレイヤーが1回の被弾で受けるダメージ
#define PLAYER_INVINCIBLE_DURATION	(30000)		//プレイヤーの無敵時間

/**************************************
構造体定義
***************************************/


/**************************************
グローバル変数
***************************************/

/**************************************
プロトタイプ宣言
***************************************/

/**************************************
コンストラクタ
***************************************/
Player::Player()
{
	mesh = new MeshContainer();
	
	mesh->Load(PLAYER_MODEL);

	collider = new TrailCollider(TrailColliderTag::Player);
	collider->active = false;
	collider->SetAddressZ(&transform.pos.z);
	collider->AddObserver(this);
}

/**************************************
デストラクタ
***************************************/
Player::~Player()
{
	SAFE_DELETE(mesh);
	SAFE_DELETE(collider);
}

/*************************************
初期化処理
**************************************/
void Player::Init()
{
	transform.pos = PLAYER_CENTER;
	transform.scale = D3DXVECTOR3(2.0f, 2.0f, 2.0f);
	active = true;

	GameParticleManager::Instance()->SetPlayerTrailParticle(&transform.pos, &active);

	cntInvincible = PLAYER_INVINCIBLE_DURATION;

	return;
}

/***************************************
終了処理
****************************************/
void Player::Uninit()
{
	active = false;
}

/****************************************
更新処理
*****************************************/
int Player::Update()
{
	if (!active)
		return STATE_CONTINUOUS;

	int stateResult = STATE_CONTINUOUS;

	if (state != NULL)
		stateResult = state->OnUpdate(this);

	//無敵時間の更新
	if (!flgInvincible)
	{
		cntInvincible--;
		if (cntInvincible == 0)
			collider->active = false;
	}

	return stateResult;
}

/*****************************************
描画処理
******************************************/
void Player::Draw()
{
	if (!active)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, quatMatrixs, shadowMatrix, mtxWorld;
	
	transform.SetWorld();
	mesh->Draw();

	TrailCollider::DrawCollider(collider);
}

/*****************************************
状態遷移
******************************************/
void Player::ChangeState(IStateMachine<Player> *next)
{
	state = next;
	state->OnStart(this);
}

/*****************************************
衝突判定通知処理
******************************************/
void Player::OnNotified(ObserveSubject* notifier)
{
	SpikeNoiseController::Instance()->SetNoise(0.5f, 20);
	hp -= PLAYER_DAMAGE;

	//無敵時間開始
	cntInvincible = PLAYER_INVINCIBLE_DURATION;
	collider->active = false;
	flgInvincible = true;
}