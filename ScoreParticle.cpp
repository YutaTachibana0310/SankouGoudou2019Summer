//=====================================
//
//スコアパーティクル処理[ScoreParticle.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "ScoreParticle.h"
#include "Framework\Easing.h"

#include <vector>
#include <array>

using namespace std;

/**************************************
マクロ定義
***************************************/
#define SCOREPARTICLE_SIZE			(10.0f)
#define SCOREPARTICLE_NUM_MAX		(256)

#define SCOREPARTICLE_TEX_NAME		("data/TEXTURE/Effect/ScoreParticle.png")
#define SCOREPARTICLE_TEX_DIV_X		(1)
#define SCOREPARTICLE_TEX_DIV_Y		(1)
#define SCOREPARTICLE_ANIM_TIME		(1)

#define SCOREPARTICLE_LIFEFRAME		(40)
#define SCOREPARTICLE_LIFE_RANGE	(10)
#define SCOREPARTICLE_SPEED_INIT	(2.0f)
#define SCOREPARTICLE_SPEED_RANGE	(2.0f)
#define SCOREPARTICLE_SPEED_TIME	(10.0f)

#define SCOREPARTICLE_DURATION		(5)
#define SCOREPARTICLE_EMIT_NUM		(10)

/**************************************
スコアパーティクル構造体
***************************************/
struct ScoreParticle
{
public:
	ScoreParticle()
	{
		transform.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	}

	bool active;

	int cntFrame;
	int lifeFrame;

	Transform transform;

	D3DXVECTOR3 moveDir;
	float speed;

	void Update();
	void GetUV(ParticleUV* pOut);
};

/**************************************
スコアパーティクルエミッタ構造体
***************************************/
struct ScoreParticleEmitter
{
	ScoreParticleEmitter(D3DXVECTOR3 *pos)
	{
		active = true;
		cntFrame = 0;
		emitDuration = SCOREPARTICLE_DURATION;
		this->pos = *pos;
	}

	bool active;

	int cntFrame;
	int emitDuration;

	D3DXVECTOR3 pos;

	void Update(array<ScoreParticle, SCOREPARTICLE_NUM_MAX>*);
};

/**************************************
グローバル変数
***************************************/
static LPDIRECT3DVERTEXBUFFER9 unitBuff, worldBuff, uvBuff;
static LPDIRECT3DTEXTURE9 texture;

static array<ScoreParticle, SCOREPARTICLE_NUM_MAX> particleContainer;
static vector<ScoreParticleEmitter> emitterContainer;

/**************************************
プロトタイプ宣言
***************************************/
DWORD EmbedScoreParticleParameter(void);		//頂点バッファへのデータ設定

/**************************************
初期化処理
***************************************/
void InitScoreParticle(int num)
{
	//単位頂点バッファ作成
	MakeParticleUnitBuffer(&D3DXVECTOR2(SCOREPARTICLE_SIZE, SCOREPARTICLE_SIZE),
		&D3DXVECTOR2(SCOREPARTICLE_TEX_DIV_X, SCOREPARTICLE_TEX_DIV_Y),
		&unitBuff);

	//SRT情報バッファ作成
	MakeTransformBuffer(SCOREPARTICLE_NUM_MAX, &worldBuff);

	//UV情報バッファ作成
	MakeUVBUffer(SCOREPARTICLE_NUM_MAX, &uvBuff);

	//テクスチャ読み込み
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXCreateTextureFromFile(pDevice, SCOREPARTICLE_TEX_NAME, &texture);
}

/**************************************
終了処理
***************************************/
void UninitScoreParticle(int num)
{
	SAFE_RELEASE(texture);
	SAFE_RELEASE(unitBuff);
	SAFE_RELEASE(worldBuff);
	SAFE_RELEASE(uvBuff);
}

/**************************************
更新処理
***************************************/
void UpdateScoreParticle(void)
{
	//エミッター更新処理
	for (auto itr = emitterContainer.begin(); itr != emitterContainer.end(); itr++)
	{
		if (!itr->active)
			continue;

		itr->Update(&particleContainer);
	}

	//パーティクル更新処理
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
void DrawScoreParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファにデータを設定
	DWORD particleCount = EmbedScoreParticleParameter();

	//ストリームソース周波数設定
	pDevice->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | particleCount);
	pDevice->SetStreamSourceFreq(1, D3DSTREAMSOURCE_INSTANCEDATA | 1);
	pDevice->SetStreamSourceFreq(2, D3DSTREAMSOURCE_INSTANCEDATA | 1);

	//テクスチャ設定
	pDevice->SetTexture(0, texture);

	//ストリームソース設定
	pDevice->SetStreamSource(0, unitBuff, 0, sizeof(ParticleUnit));
	pDevice->SetStreamSource(1, worldBuff, 0, sizeof(Transform));
	pDevice->SetStreamSource(2, uvBuff, 0, sizeof(ParticleUV));

	//描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NUM_VERTEX, 0, NUM_POLYGON);

	//ストリームソース周波数復元
	pDevice->SetStreamSourceFreq(0, 1);
	pDevice->SetStreamSourceFreq(1, 1);
	pDevice->SetStreamSourceFreq(2, 1);
}

/**************************************
頂点バッファへのデータ設定
***************************************/
DWORD EmbedScoreParticleParameter(void)
{
	DWORD particleCount = 0;

	//頂点バッファをロック
	Transform *pTransform;
	worldBuff->Lock(0, 0, (void**)&pTransform, 0);
	ParticleUV *pUV;
	uvBuff->Lock(0, 0, (void**)&pUV, 0);

	//頂点バッファにデータを設定
	for (auto itr = particleContainer.begin(); itr != particleContainer.end(); itr++)
	{
		if (!itr->active)
			continue;

		*pTransform = itr->transform;
		itr->GetUV(pUV);

		pTransform++;
		pUV++;

		particleCount ++;
	}

	//頂点バッファをアンロック
	worldBuff->Unlock();
	uvBuff->Unlock();

	return particleCount;
}

/**************************************
パーティクル更新処理
***************************************/
void ScoreParticle::Update()
{
	const float EndSpeed = 0.2f;
	const float InitScale = 1.0f, EndScale = 0.0f;

	//移動処理
	float tSpeed = (float)cntFrame / (float)SCOREPARTICLE_SPEED_TIME;
	float currentSpeed = Easing<float>::GetEasingValue(tSpeed, &speed, &EndSpeed, EasingType::InExponential);
	transform.pos += moveDir * currentSpeed;

	//スケール処理
	float tScale = (float)cntFrame / (float)lifeFrame;
	float currentScale = Easing<float>::GetEasingValue(tScale, &InitScale, &EndScale, EasingType::OutExponential);
	transform.scale = D3DXVECTOR3(currentScale, currentScale, currentScale);

	//寿命判定
	cntFrame++;
	if (cntFrame > lifeFrame)
	{
		active = false;
	}
}

/**************************************
UV座標決定処理
***************************************/
void ScoreParticle::GetUV(ParticleUV* pOut)
{
	static float sizeX = 1.0f / SCOREPARTICLE_TEX_DIV_X;

	static float sizeY = 1.0f / SCOREPARTICLE_TEX_DIV_Y;

	int x = cntFrame % SCOREPARTICLE_TEX_DIV_X;
	int y = cntFrame / SCOREPARTICLE_TEX_DIV_X;
	pOut->u = sizeX * x;
	pOut->v = sizeY * y;
}

/**************************************
エミッター更新処理
***************************************/
void ScoreParticleEmitter::Update(array<ScoreParticle, SCOREPARTICLE_NUM_MAX>* container)
{
	//放出処理
	for (int i = 0; i < SCOREPARTICLE_EMIT_NUM; i++)
	{
		for (auto itr = container->begin(); itr != container->end(); itr++)
		{
			if (itr->active)
				continue;

			itr->moveDir.x = RandomRangef(-1.0f, 1.0f);
			itr->moveDir.y = RandomRangef(-1.0f, 1.0f);
			itr->moveDir.z = RandomRangef(-1.0f, 1.0f);

			itr->lifeFrame = SCOREPARTICLE_LIFEFRAME + RandomRange(-SCOREPARTICLE_LIFE_RANGE, SCOREPARTICLE_LIFE_RANGE);
			itr->cntFrame = 0;

			itr->speed = SCOREPARTICLE_SPEED_INIT + RandomRangef(-SCOREPARTICLE_SPEED_RANGE, SCOREPARTICLE_SPEED_RANGE);
			itr->transform.pos = pos;

			itr->active = true;
			break;
		}
	}

	//寿命判定
	cntFrame++;
	if (cntFrame > emitDuration)
	{
		active = false;
	}
}

/**************************************
スコアパーティクル発生処理
***************************************/
void SetScoreParticle(D3DXVECTOR3 pos)
{
	//未使用のエミッターを検索
	for (auto itr = emitterContainer.begin(); itr != emitterContainer.end(); itr++)
	{
		if (itr->active)
			continue;

		itr->pos = pos;
		itr->cntFrame = 0;
		itr->active = true;
		return;
	}

	//新たにエミッターを作成してコンテナに追加
	emitterContainer.push_back(ScoreParticleEmitter(&pos));
}