//=====================================
//
//ボム処理[PlayerBomber.cpp]
//Author:GP12B332 12 権頭
//
//=====================================
#include "PlayerBomber.h"
#include "camera.h"

/**************************************
マクロ定義
***************************************/
#define PLAYERBOMBER_TEXTURE_NAME	"data/MODEL/airplane000.x"

#define BOMBER_X		(30)
#define BOMBER_Y		(30)
#define BOMBER_Z		(30)

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
	transform.rot = D3DXVECTOR3(0.0f, D3DXToRadian(180.0f), 0.0f);

	velocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, quatMatrixs, mtxWorld, view, invView;
	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	// スケールを反映
	D3DXMatrixScaling(&mtxScl, transform.scale.y, transform.scale.x, transform.scale.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, transform.rot.y, transform.rot.x, transform.rot.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	//逆行列を掛ける
	view = GetMtxView();
	D3DXMatrixInverse(&view, NULL, &invView);
	invView._41 = 0.0f;
	invView._42 = 0.0f;
	invView._43 = 0.0f;
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &invView);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, transform.pos.x, transform.pos.y, transform.pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

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
	if (instanceCount == 0)
	{
		//インスタンスが残っていなければテクスチャ解放

	}
}

/**************************************
ホーミング対象のアドレスを取得
引数(ホーミング対象のアドレス、ボムのセット位置)
***************************************/
void PlayerBomber::Set(D3DXVECTOR3 *pos, D3DXVECTOR3 initpos)
{
	//active = true;
	Init();
	transform.pos = initpos;
	targetPos = pos;
	cntFrame = reachFrame = 120;
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

	float time = cntFrame;

	D3DXVECTOR3 diff = *targetPos - transform.pos;

	D3DXVECTOR3 acceleration = (diff - velocity * time) * 2.0f / (time * time);

	velocity += acceleration;

	cntFrame--;
}
