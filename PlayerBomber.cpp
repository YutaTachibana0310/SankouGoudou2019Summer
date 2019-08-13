//=====================================
//
//ボム処理[PlayerBomber.cpp]
//Author:GP12B332 12 権頭
//
//=====================================
#include "PlayerBomber.h"
#include "camera.h"
#include "GameParticleManager.h"

/**************************************
マクロ定義
***************************************/
#define BOMBER_MOVE (10.0f)
/**************************************
構造体定義
***************************************/

/**************************************
staticメンバ
***************************************/
int PlayerBomber::instanceCount = 0;				//インスタンスカウンタ

/**************************************
グローバル変数
***************************************/

/**************************************
プロトタイプ宣言
***************************************/


/**************************************
初期化処理
***************************************/
void PlayerBomber::Init(void)
{
	active = true;
	cntFrame = 0;
	reachFrame = 0;

	transform.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	transform.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	float x = RandomRangef(-BOMBER_MOVE, BOMBER_MOVE);
	float y = RandomRangef(-BOMBER_MOVE, BOMBER_MOVE);
	velocity = D3DXVECTOR3(x, y, 0.0f);

	GameParticleManager::Instance()->SetPlayerBomberParticle(&transform.pos, &active);
}

/**************************************
終了処理
***************************************/
void PlayerBomber::Uninit(void)
{
	active = false;
}

/**************************************
更新処理
***************************************/
void PlayerBomber::Update(void)
{
	if (!active)
		return;
	
	CalcBomber();
	transform.pos += velocity;
	
	if (cntFrame == 0)
		Uninit();

}

/**************************************
描画処理
***************************************/
void PlayerBomber::Draw(void)
{
	if (!active)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	transform.SetWorld();

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

/**************************************
コンストラクタ
***************************************/
PlayerBomber::PlayerBomber()
{
	active = false;
	instanceCount++;
}

/**************************************
デストラクタ
***************************************/
PlayerBomber::~PlayerBomber()
{
	instanceCount--;
}

/**************************************
ホーミング対象のアドレスを取得
引数(ホーミング対象のアドレス、ボムのセット位置)
***************************************/
void PlayerBomber::Set(D3DXVECTOR3 pos, D3DXVECTOR3 initpos)
{
	transform.pos = initpos;
	targetPos = pos;
	cntFrame = reachFrame = 30;
}


/***************************************
加速度の計算処理
****************************************/
void PlayerBomber::CalcBomber(void)
{
	if (cntFrame <= 0)
	{
		return;
	}

	float time = (float)cntFrame;

	D3DXVECTOR3 diff = targetPos - transform.pos;

	D3DXVECTOR3 acceleration = (diff - velocity * time) * 2.0f / (time * time);

	velocity += acceleration;

	cntFrame--;
}
