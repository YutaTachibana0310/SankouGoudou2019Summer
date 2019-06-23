//=====================================
//
//ベースパーティクルコントローラ処理[BaseParticleController.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "BaseParticleController.h"
#include <algorithm>

using namespace std;

/**************************************
マクロ定義
***************************************/

/**************************************
構造体定義
***************************************/

/**************************************
staticメンバ
***************************************/
LPDIRECT3DVERTEXDECLARATION9 BaseParticleController::declare;	//頂点宣言
LPD3DXEFFECT BaseParticleController::effect;					//エフェクト
LPDIRECT3DINDEXBUFFER9 BaseParticleController::indexBuff;		//インデックバッファ
LPDIRECT3DVERTEXBUFFER9 BaseParticleController::transformBuff;	//トランスフォーム頂点バッファ
LPDIRECT3DVERTEXBUFFER9 BaseParticleController::uvBuff;			//UV情報頂点バッファ
UINT BaseParticleController::instanceCount;						//インスタンス数
D3DXHANDLE BaseParticleController::hMtxView;					//エフェクトのビュー行列へのハンドル
D3DXHANDLE BaseParticleController::hMtxProj;					//エフェクトのプロジェクション行列へのハンドル
D3DXHANDLE BaseParticleController::hMtxInvView;					//エフェクトのビュー逆行列へのハンドル

/**************************************
コンストラクタ
***************************************/
BaseParticleController::BaseParticleController()
{
	if (instanceCount == 0)
	{
		MakeVertexDeclaration();
		MakeTransformBuffer();
		MakeUVBuffer();
		MakeIndexBuffer();
		LoadEffect();
	}
	instanceCount++;
}

/**************************************
デストラクタ
***************************************/
BaseParticleController::~BaseParticleController()
{
	SAFE_RELEASE(unitBuff);
	SAFE_RELEASE(texture);

	instanceCount--;
	if (instanceCount == 0)
	{
		SAFE_RELEASE(declare);
		SAFE_RELEASE(transformBuff);
		SAFE_RELEASE(uvBuff);
		SAFE_RELEASE(indexBuff);
		SAFE_RELEASE(effect);
	}
}

/**************************************
終了処理
***************************************/
void BaseParticleController::Uninit()
{
	vector<BaseParticle*>().swap(particleContainer);

	vector<BaseEmitter*>().swap(emitterContainer);

}

/**************************************
更新処理
***************************************/
void BaseParticleController::Update()
{
	//エミッタ更新
	for (BaseEmitter *emitter : emitterContainer)
	{
		if (!emitter->active)
			continue;

		emitter->Update();
	}

	//パーティクル放出
	Emit();

	//パーティクル更新
	for (BaseParticle *particle : particleContainer)
	{
		if (!particle->active)
			continue;

		particle->Update();
	}
}

/**************************************
描画処理
***************************************/
bool BaseParticleController::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//各パーティクルのパラメータを頂点バッファにセット
	UINT particleCount = 0;
	particleCount = EmbedParameterTransform();
	EmbedParameterUV();

	if (particleCount == 0)
		return false;

	//ストリームソース設定
	pDevice->SetStreamSource(0, unitBuff, 0, sizeof(ParticleUnit));
	pDevice->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | particleCount);

	//テクスチャ設定
	pDevice->SetTexture(0, texture);

	//描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NUM_VERTEX, 0, NUM_POLYGON);

	return true;
}

/**************************************
パーティクル単位バッファ作成処理
***************************************/
void BaseParticleController::MakeUnitBuffer(const D3DXVECTOR2 *size, const D3DXVECTOR2 *texDiv)
{
	if (unitBuff != NULL)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->CreateVertexBuffer(sizeof(ParticleUnit) * NUM_VERTEX, 0, 0, D3DPOOL_MANAGED, &unitBuff, 0);

	ParticleUnit *p;
	unitBuff->Lock(0, 0, (void**)&p, 0);

	//単位サイズ設定
	p[0].vtx = D3DXVECTOR3(-size->x / 2.0f, size->y / 2.0f, 0.0f);
	p[1].vtx = D3DXVECTOR3(size->x / 2.0f, size->y / 2.0f, 0.0f);
	p[2].vtx = D3DXVECTOR3(-size->x / 2.0f, -size->y / 2.0f, 0.0f);
	p[3].vtx = D3DXVECTOR3(size->x / 2.0f, -size->y / 2.0f, 0.0f);

	//単位UV設定
	float u = 1.0f / texDiv->x;
	float v = 1.0f / texDiv->y;
	p[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	p[1].tex = D3DXVECTOR2(u, 0.0f);
	p[2].tex = D3DXVECTOR2(0.0f, v);
	p[3].tex = D3DXVECTOR2(u, v);

	unitBuff->Unlock();
}

/**************************************
トランスフォームバッファ作成処理
***************************************/
void BaseParticleController::MakeTransformBuffer()
{
	if (transformBuff != NULL)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->CreateVertexBuffer(sizeof(Transform) * PARTICLE_NUM_MAX, 0, 0, D3DPOOL_MANAGED, &transformBuff, 0);
}

/**************************************
UVバッファ作成処理
***************************************/
void BaseParticleController::MakeUVBuffer()
{
	if (uvBuff != NULL)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->CreateVertexBuffer(sizeof(ParticleUV) * PARTICLE_NUM_MAX, 0, 0, D3DPOOL_MANAGED, &uvBuff, 0);
}

/**************************************
頂点宣言作成処理
***************************************/
void BaseParticleController::MakeVertexDeclaration()
{
	if (declare != NULL)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DVERTEXELEMENT9 elems[] =
	{
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },	//単位頂点（頂点座標）
		{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },	//単位頂点（テクスチャ座標）
		{ 1, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1 },	//ワールド変換情報（ポジション）
		{ 1, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 2 },	//ワールド変換情報（ローテーション）
		{ 1, 24, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 3 },	//ワールド変換情報（スケール）
		{ 2, 0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 4 },	//個別のテクスチャ
		D3DDECL_END()
	};
	pDevice->CreateVertexDeclaration(elems, &declare);
}

/**************************************
エフェクト読み込み処理
***************************************/
void BaseParticleController::LoadEffect()
{
	if (effect != NULL)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXCreateEffectFromFile(pDevice, "data/EFFECT/particle3D.cfx", 0, 0, D3DXSHADER_SKIPVALIDATION, 0, &effect, 0);

	hMtxView = effect->GetParameterByName(NULL, "mtxView");
	hMtxProj = effect->GetParameterByName(NULL, "mtxProj");
	hMtxInvView = effect->GetParameterByName(NULL, "mtxInvView");
}

/**************************************
インデックバッファ作成処理
***************************************/
void BaseParticleController::MakeIndexBuffer()
{
	if (indexBuff != NULL)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	WORD index[] = { 0, 1, 2, 2, 1, 3 };
	pDevice->CreateIndexBuffer(sizeof(index), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &indexBuff, 0);

	void* p;
	indexBuff->Lock(0, 0, &p, 0);
	memcpy(p, index, sizeof(index));
	indexBuff->Unlock();
}

/**************************************
テクスチャ読み込み処理
***************************************/
void BaseParticleController::LoadTexture(const char* filePath)
{
	if (texture != NULL)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	texture = CreateTextureFromFile((LPSTR)filePath, pDevice);
}

/**************************************
描画開始処理
***************************************/
void BaseParticleController::BeginDraw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//レンダーステート切り替え
	pDevice->SetRenderState(D3DRS_LIGHTING, false);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

	//ビュー行列、プロジェクション行列、ビュー逆行列を取得
	D3DXMATRIX view, proj, invView;
	pDevice->GetTransform(D3DTS_VIEW, &view);
	pDevice->GetTransform(D3DTS_PROJECTION, &proj);
	D3DXMatrixInverse(&invView, NULL, &view);
	invView._41 = invView._42 = invView._43 = 0.0f;

	//シェーダに各行列を設定
	effect->SetMatrix(hMtxView, &view);
	effect->SetMatrix(hMtxProj, &proj);
	effect->SetMatrix(hMtxInvView, &invView);

	//各頂点バッファを設定
	pDevice->SetStreamSource(1, transformBuff, 0, sizeof(Transform));
	pDevice->SetStreamSource(2, uvBuff, 0, sizeof(ParticleUV));
	pDevice->SetIndices(indexBuff);
	pDevice->SetVertexDeclaration(declare);

	//ストリーム周波数設定
	pDevice->SetStreamSourceFreq(1, D3DSTREAMSOURCE_INSTANCEDATA | 1);
	pDevice->SetStreamSourceFreq(2, D3DSTREAMSOURCE_INSTANCEDATA | 1);
	
	//シェーダによる描画開始
	effect->Begin(0, 0);
	effect->BeginPass(0);
}

/**************************************
描画終了処理
***************************************/
void BaseParticleController::EndDraw()
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//シェーダによる描画終了
	effect->EndPass();
	effect->End();

	//レンダーステート復元
	pDevice->SetRenderState(D3DRS_LIGHTING, true);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);

	//ストリーム周波数復元
	pDevice->SetStreamSourceFreq(0, 1);
	pDevice->SetStreamSourceFreq(1, 1);
	pDevice->SetStreamSourceFreq(2, 1);
}

/**************************************
トランスフォーム情報埋め込み処理
***************************************/
UINT BaseParticleController::EmbedParameterTransform()
{
	if (particleContainer.size() > PARTICLE_NUM_MAX)
		return 0;

	UINT count = 0;
	Transform *pTr;
	transformBuff->Lock(0, 0, (void**)&pTr, 0);
	for (BaseParticle *particle : particleContainer)
	{
		if (!particle->active)
			continue;

		*pTr = particle->transform;
		pTr++;
		count++;
	}

	return count;
}

/**************************************
UV情報埋め込み処理
***************************************/
UINT BaseParticleController::EmbedParameterUV()
{
	if (particleContainer.size() > PARTICLE_NUM_MAX)
		return 0;

	UINT count = 0;
	ParticleUV *pUV;
	uvBuff->Lock(0, 0, (void**)&pUV, 0);
	for (BaseParticle *particle : particleContainer)
	{
		if (!particle->active)
			continue;

		*pUV = particle->uv;
		pUV++;
		count++;
	}

	return count;
}

/**************************************
エミッタセット処理
***************************************/
void BaseParticleController::SetEmitter(D3DXVECTOR3 *pos)
{
	auto emitter = find_if(emitterContainer.begin(), emitterContainer.end(), [](BaseEmitter* emitter)
	{
		return !emitter->active;
	});

	if (emitter == emitterContainer.end())
		return;

	(*emitter)->transform.pos = *pos;
	(*emitter)->Init();

}