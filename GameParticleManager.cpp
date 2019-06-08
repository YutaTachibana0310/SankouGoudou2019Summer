//=====================================
//
//ゲームパーティクルマネージャ処理[GameParticleManager.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "GameParticleManager.h"

#include "ScoreParticle.h"

#ifdef _DEBUG
#include "debugWindow.h"
#endif

/**************************************
マクロ定義
***************************************/
#define GAMEPARTICLE_EFFECT_NAME		"data/EFFECT/particle3D.fx"

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/
static LPDIRECT3DVERTEXDECLARATION9 vtxDeclare;
static LPD3DXEFFECT effect;
static LPDIRECT3DINDEXBUFFER9 indexBuff;

/**************************************
プロトタイプ宣言
***************************************/
void GameParticleDebugWindow(void);

/**************************************
初期化処理
***************************************/
void InitGameParticleManager(int num)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点宣言作成
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
	pDevice->CreateVertexDeclaration(elems, &vtxDeclare);

	//インデックスバッファ作成
	WORD index[6] = { 0, 1, 2, 2, 1, 3 };
	pDevice->CreateIndexBuffer(sizeof(index), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &indexBuff, NULL);

	void *p;
	indexBuff->Lock(0, 0, &p, 0);
	memcpy(p, index, sizeof(index));
	indexBuff->Unlock();

	//テクスチャ読み込み
	D3DXCreateEffectFromFile(pDevice, GAMEPARTICLE_EFFECT_NAME, 0, 0, 0, 0, &effect, 0);

	//各パーティクル初期化
	InitScoreParticle(0);
}

/**************************************
終了処理
***************************************/
void UninitGameParticleManager(int num)
{
	UninitScoreParticle(0);

	SAFE_RELEASE(vtxDeclare);
	SAFE_RELEASE(indexBuff);
	SAFE_RELEASE(effect);
}

/**************************************
更新処理
***************************************/
void UpdateGameParticleManager(void)
{
#ifdef _DEBUG
	GameParticleDebugWindow();
#endif
	UpdateScoreParticle();
}

/**************************************
描画処理
***************************************/
void DrawGameParticleManager(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//レンダーステート切り替え
	pDevice->SetRenderState(D3DRS_LIGHTING, false);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

	//ビュー行列、プロジェクション行列、ビュー逆行列を取得
	D3DXMATRIX view, projection, invView;
	pDevice->GetTransform(D3DTS_VIEW, &view);
	pDevice->GetTransform(D3DTS_PROJECTION, &projection);
	D3DXMatrixInverse(&invView, NULL, &view);
	invView._41 = invView._42 = invView._43 = 0.0f;

	//シェーダに各行列を設定
	effect->SetMatrix("mtxView", &view);
	effect->SetMatrix("mtxProj", &projection);
	effect->SetMatrix("mtxInvView", &invView);

	//インデックスバッファと頂点宣言を設定
	pDevice->SetIndices(indexBuff);
	pDevice->SetVertexDeclaration(vtxDeclare);

	//シェーダによる描画開始
	effect->Begin(0, 0);
	effect->BeginPass(0);

	//描画
	DrawScoreParticle();

	//シェーダによる描画終了
	effect->EndPass();
	effect->End();

	//レンダーステート復元
	pDevice->SetRenderState(D3DRS_LIGHTING, true);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}

#ifdef _DEBUG
/**************************************
デバッグウィンドウ
***************************************/
void GameParticleDebugWindow(void)
{
	BeginDebugWindow("GameParticle");
	
	if (DebugButton("ScoreParticle"))
		SetScoreParticle(D3DXVECTOR3(0.0f, 0.0f, 50.0f));

	EndDebugWindow("GameParticle");
}
#endif