//=====================================
//
//プレイヤーバレットパーティクル処理[PlayerBulletParticle.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "PlayerBulletParticle.h"
#include "Framework\Easing.h"

#include <vector>
#include <array>

using namespace std;

/**************************************
マクロ定義
***************************************/
#define PLAYERBULLETPARTICLE_TEXTURE_NAME	"data/TEXTURE/Effect/PlayerBulletParticle.png"
#define PLAYERBULLETPARTCILE_NUM_MAX		(4096)
#define PLAYERBULLETPARTICLE_SIZE			(2.0f)

#define PLAYERBULLETPARTICLE_LIFEFRAME		(10)
#define PLAYERBULLETPARTTCLE_LIFE_RANGE		(3)

/**************************************
プレイヤーバレットパーティクル構造体
***************************************/
struct PlayerBulletParticle
{
	bool active;
	int cntFrame;
	int lifeFrame;
	Transform transform;
	D3DXVECTOR3 moveDir;
	float speed;

	void Update();
};

/**************************************
プレイヤーバレットパーティクルエミッタ構造体
***************************************/
struct PlayerBulletParticleEmitter
{
	PlayerBulletParticleEmitter(D3DXVECTOR3 *pPos, bool *pActive, const D3DXVECTOR3 *edgeRight, const D3DXVECTOR3 *edgeLeft)
	{
		parentActive = pActive;
		parentPos = pPos;
		this->edgeLeft = *edgeLeft;
		this->edgeRight = *edgeRight;
		active = true;
	}

	bool active;
	bool *parentActive;						//親のアクティブポインタ
	D3DXVECTOR3 *parentPos;					//親の座標ポインタ
	D3DXVECTOR3 edgeRight, edgeLeft;		//パーティクル発生の端点

	void Update(array<PlayerBulletParticle, PLAYERBULLETPARTCILE_NUM_MAX>*);
};

/**************************************
グローバル変数
***************************************/
static LPDIRECT3DVERTEXBUFFER9 unitBuff, transformBuffer, uvBuffer;
static LPDIRECT3DTEXTURE9 texture;

static array<PlayerBulletParticle, PLAYERBULLETPARTCILE_NUM_MAX> particleContainer;
static vector<PlayerBulletParticleEmitter> emitterContainer;

/**************************************
プロトタイプ宣言
***************************************/
DWORD EmbedPlayerBulletParticleParameter(void);		//頂点バッファへのデータ設定

/**************************************
初期化処理
***************************************/
void InitPlayerBulletParticle(int num)
{
	//単位頂点バッファ作成
	MakeParticleUnitBuffer(&D3DXVECTOR2(PLAYERBULLETPARTICLE_SIZE, PLAYERBULLETPARTICLE_SIZE),
		&D3DXVECTOR2(1.0f, 1.0f),
		&unitBuff);

	//SRT情報バッファ作成
	MakeTransformBuffer(PLAYERBULLETPARTCILE_NUM_MAX, &transformBuffer);

	//UV情報バッファ作成
	MakeTransformBuffer(PLAYERBULLETPARTCILE_NUM_MAX, &uvBuffer);

	//テクスチャ読み込み
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXCreateTextureFromFile(pDevice, PLAYERBULLETPARTICLE_TEXTURE_NAME, &texture);
}

/**************************************
終了処理
***************************************/
void UninitPlayerBulletParticle(int num)
{
	SAFE_RELEASE(texture);
	SAFE_RELEASE(unitBuff);
	SAFE_RELEASE(transformBuffer);
	SAFE_RELEASE(uvBuffer);
}

/**************************************
更新処理
***************************************/
void UpdatePlayerBulletParticle(void)
{
	for (auto itr = emitterContainer.begin(); itr != emitterContainer.end(); itr++)
	{
		if (!itr->active)
			continue;

		itr->Update(&particleContainer);
	}

	for (auto itr = particleContainer.begin(); itr != particleContainer.end(); itr++)
	{
		if (!itr->active)
			continue;

		itr->Update();
	}
}

/**************************************
描画処理
***************************************/
void DrawPlayerBulletParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//加算合成
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//頂点バッファにデータを設定
	DWORD particleCount = EmbedPlayerBulletParticleParameter();

	//ストリームソース周波数設定
	pDevice->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | particleCount);
	pDevice->SetStreamSourceFreq(1, D3DSTREAMSOURCE_INSTANCEDATA | 1);
	pDevice->SetStreamSourceFreq(2, D3DSTREAMSOURCE_INSTANCEDATA | 1);

	//テクスチャ設定
	pDevice->SetTexture(0, texture);

	//ストリームソース設定
	pDevice->SetStreamSource(0, unitBuff, 0, sizeof(ParticleUnit));
	pDevice->SetStreamSource(1, transformBuffer, 0, sizeof(Transform));
	pDevice->SetStreamSource(2, uvBuffer, 0, sizeof(ParticleUV));

	//描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NUM_VERTEX, 0, NUM_POLYGON);

	//ストリームソース周波数設定
	pDevice->SetStreamSourceFreq(0, 1);
	pDevice->SetStreamSourceFreq(1, 1);
	pDevice->SetStreamSourceFreq(2, 1);

	//通常描画に復帰
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

/**************************************
頂点バッファへのデータ設定
***************************************/
DWORD EmbedPlayerBulletParticleParameter(void)
{
	DWORD particleCount = 0;

	//頂点バッファをロック
	Transform *pTransform;
	transformBuffer->Lock(0, 0, (void**)&pTransform, 0);

	//頂点バッファにデータを設定
	for (auto itr = particleContainer.begin(); itr != particleContainer.end(); itr++)
	{
		if (!itr->active)
			continue;

		*pTransform = itr->transform;

		pTransform++;
		particleCount++;
	}

	//頂点バッファをアンロック
	transformBuffer->Unlock();

	return particleCount;
}

/**************************************
パーティクル更新処理
***************************************/
void PlayerBulletParticle::Update()
{
	//移動処理
	transform.pos += moveDir * speed;

	//寿命判定
	cntFrame++;
	if (cntFrame > lifeFrame)
	{
		active = false;
	}
}

/**************************************
エミッター更新処理
***************************************/
void PlayerBulletParticleEmitter::Update(array<PlayerBulletParticle, PLAYERBULLETPARTCILE_NUM_MAX>* container)
{
	const int EmitNum = 50;
	const float Speed = 2.0f;

	//放出処理
	int countEmit = 0;
	for (auto itr = container->begin(); itr != container->end(); itr++)
	{
		if (itr->active)
			continue;

		itr->moveDir.x = RandomRangef(-1.0f, 1.0f);
		itr->moveDir.y = RandomRangef(-1.0f, 1.0f);
		itr->moveDir.z = -2.0f;
		D3DXVec3Normalize(&itr->moveDir, &itr->moveDir);

		itr->lifeFrame = PLAYERBULLETPARTICLE_LIFEFRAME + RandomRange(-PLAYERBULLETPARTTCLE_LIFE_RANGE, PLAYERBULLETPARTTCLE_LIFE_RANGE);
		itr->cntFrame = 0;

		itr->speed = Speed;

		float t = RandomRangef(0.0f, 1.0f);
		itr->transform.pos = Easing<D3DXVECTOR3>::GetEasingValue(t, &edgeLeft, &edgeRight, EasingType::Linear);
		itr->transform.pos.z = parentPos->z;

		itr->transform.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		itr->transform.scale.x += fabsf(itr->moveDir.x)* 10.0f;
		itr->transform.scale.y += fabsf(itr->moveDir.y)* 10.0f;

		itr->active = true;

		countEmit++;
		if(countEmit == EmitNum)
			break;
	}


	//寿命判定
	if (!*parentActive)
	{
		active = false;
	}
}

/**************************************
プレイヤーバレット発生処理
***************************************/
void SetPlayerBulletParticle(D3DXVECTOR3 *pPos, bool *pActive, const D3DXVECTOR3 *edgeRight, const D3DXVECTOR3 *edgeLeft)
{
	//未使用のエミッターの中からセット
	for (auto itr = emitterContainer.begin(); itr != emitterContainer.end(); itr++)
	{
		if (itr->active)
			continue;

		itr->active = true;
		itr->parentActive = pActive;
		itr->parentPos = pPos;
		itr->edgeLeft = *edgeLeft;
		itr->edgeRight = *edgeRight;
		return;
	}

	//新たにエミッターを作成してコンテナに追加
	emitterContainer.push_back(PlayerBulletParticleEmitter(pPos, pActive, edgeRight, edgeLeft));
}