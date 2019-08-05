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
#define PLAYER_MODEL				"data/MODEL/player.x"
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
	//アニメーション初期化
	animation = new AnimContainer();
	animation->LoadXFile(PLAYER_MODEL, "Player");
	animation->SetupCallbackKeyFrames("Flying");
	animation->SetupCallbackKeyFrames("Attack");
	animation->SetupCallbackKeyFrames("FireBomber");
	animation->LoadAnimation("Flying", PlayerAnimID::Flying);
	animation->LoadAnimation("Attack", PlayerAnimID::Attack);
	animation->LoadAnimation("FireBomber", PlayerAnimID::FireBomber);
	animation->SetShiftTime(PlayerAnimID::Flying, 0.2f);
	animation->SetShiftTime(PlayerAnimID::Attack, 0.2f);
	animation->SetShiftTime(PlayerAnimID::FireBomber, 0.2f);

	collider = new TrailCollider(TrailColliderTag::Player);
	collider->active = false;
	collider->SetAddressZ(&transform.pos.z);
	collider->AddObserver(this);

	animation->ChangeAnim(PlayerAnimID::Flying, 1.5f, true);
}

/**************************************
デストラクタ
***************************************/
Player::~Player()
{
	SAFE_DELETE(animation);
	SAFE_DELETE(collider);
}

/*************************************
初期化処理
**************************************/
void Player::Init()
{
	transform.pos = PLAYER_CENTER;
	transform.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
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

	//アニメーションの更新
	animation->Update(1.0f / 60.0f);

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
	D3DXMATRIX mtxWorld = transform.GetMatrix();
	D3DMATERIAL9 matDef;

	pDevice->GetMaterial(&matDef);
	
	transform.SetWorld();
	animation->Draw(&mtxWorld);

	pDevice->SetMaterial(&matDef);

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

/*****************************************
アニメーション切り替え処理
******************************************/
void Player::ChangeAnim(PlayerAnimID next)
{
	static const float shitTime[PlayerAnimID::PlayerAnimMax] = {
		1.5f,
		7.0f,
		1.0f
	};

	animation->ChangeAnim(next, shitTime[next], true);
}