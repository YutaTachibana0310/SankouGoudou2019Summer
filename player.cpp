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
#define PLAYER_MODEL	"data/MODEL/airplane000.x"
#define PLAYER_DAMAGE	(10.0f)

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
	transform.rot = D3DXVECTOR3(0.0f, D3DXToRadian(180.0f), 0.0f);
	active = true;

	GameParticleManager::Instance()->SetPlayerTrailParticle(&transform.pos, &active);
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
	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	// スケールを反映
	D3DXMatrixScaling(&mtxScl, transform.scale.y, transform.scale.x, transform.scale.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, transform.rot.y, transform.rot.x, transform.rot.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, transform.pos.x, transform.pos.y, transform.pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

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
}