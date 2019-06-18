//=====================================
//
//ゲームパーティクルマネージャ処理[GameParticleManager.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "GameParticleManager.h"

#include "ScoreParticle.h"
#include "PlayerBulletParticle.h"

#include "PostEffect\ScreenObject.h"
#include "PostEffect\CrossFilterController.h"
#include "PostEffect\BloomController.h"

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

//レンダーターゲット関連
static LPDIRECT3DTEXTURE9 renderTexture;
static LPDIRECT3DSURFACE9 renderSurface;
static D3DVIEWPORT9 viewPort;
static ScreenObject *screenObj;

/**************************************
プロトタイプ宣言
***************************************/
namespace GameParticle
{
	void DrawDebugWindow(void);					//デバッグ表示
	void CreateRenderTarget(void);				//レンダーターゲット作成
	void ChangeRenderParameter(void);			//レンダリング設定切り替え
	void RestoreRenderParameter(LPDIRECT3DSURFACE9 oldSuf, _D3DVIEWPORT9 oldViewport);			//レンダリング設定復元
}


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

	//エフェクト読み込み
	D3DXCreateEffectFromFile(pDevice, GAMEPARTICLE_EFFECT_NAME, 0, 0, 0, 0, &effect, 0);

	//レンダーターゲット作成
	GameParticle::CreateRenderTarget();

	//各パーティクル初期化
	InitScoreParticle(0);
	InitPlayerBulletParticle(0);
}

/**************************************
終了処理
***************************************/
void UninitGameParticleManager(int num)
{
	UninitScoreParticle(0);
	UninitPlayerBulletParticle(0);

	SAFE_RELEASE(vtxDeclare);
	SAFE_RELEASE(indexBuff);
	SAFE_RELEASE(effect);
	SAFE_RELEASE(renderSurface);
	SAFE_RELEASE(renderTexture);
	SAFE_DELETE(screenObj);
}

/**************************************
更新処理
***************************************/
void UpdateGameParticleManager(void)
{
#ifdef _DEBUG
	GameParticle::DrawDebugWindow();
#endif

	UpdateScoreParticle();
	UpdatePlayerBulletParticle();
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

	//レンダリング設定切り替え
	D3DVIEWPORT9 oldViewport;
	LPDIRECT3DSURFACE9 oldSuf;
	pDevice->GetViewport(&oldViewport);
	pDevice->GetRenderTarget(0, &oldSuf);
	GameParticle::ChangeRenderParameter();

	//シェーダによる描画開始
	effect->Begin(0, 0);
	effect->BeginPass(0);

	//描画
	DrawScoreParticle();
	DrawPlayerBulletParticle();

	//シェーダによる描画終了
	effect->EndPass();
	effect->End();

#ifndef _DEBUG	//クロスフィルタはRelease版でのみ適用する
	//ポストエフェクト
	CrossFilterController::Instance()->Draw(renderTexture);
#endif // !_DEBUG

	//全ての結果を元のレンダーターゲットに描画
	GameParticle::RestoreRenderParameter(oldSuf, oldViewport);
	screenObj->Draw();

	//レンダーステート復元
	pDevice->SetRenderState(D3DRS_LIGHTING, true);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

/**************************************
レンダーターゲット作成
***************************************/
void GameParticle::CreateRenderTarget()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//レンダーターゲット作成
	pDevice->CreateTexture(SCREEN_WIDTH,
		SCREEN_HEIGHT,
		1,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_X8R8G8B8,
		D3DPOOL_DEFAULT,
		&renderTexture,
		0);

	//サーフェイス取得
	renderTexture->GetSurfaceLevel(0, &renderSurface);

	//ビューポート作成
	pDevice->GetViewport(&viewPort);
	viewPort.Width = SCREEN_WIDTH;
	viewPort.Height = SCREEN_HEIGHT;

	//描画用スクリーンオブジェクト作成
	screenObj = new ScreenObject();
}

/**************************************
レンダリング設定切り替え
***************************************/
void GameParticle::ChangeRenderParameter()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//レンダーターゲット切り替え
	pDevice->SetRenderTarget(0, renderSurface);
	pDevice->SetViewport(&viewPort);
	pDevice->Clear(0, 0, D3DCLEAR_TARGET, 0, 0.0f, 0);

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
}

/**************************************
レンダリング設定復元
***************************************/
void GameParticle::RestoreRenderParameter(LPDIRECT3DSURFACE9 oldSuf, _D3DVIEWPORT9 oldViewport)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderTarget(0, oldSuf);
	pDevice->SetTexture(0, renderTexture);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	pDevice->SetViewport(&oldViewport);
	SAFE_RELEASE(oldSuf);
}

#ifdef _DEBUG
/**************************************
デバッグウィンドウ
***************************************/
void GameParticle::DrawDebugWindow(void)
{
	BeginDebugWindow("GameParticle");
	
	{
		if (DebugButton("ScoreParticle"))
			SetScoreParticle(D3DXVECTOR3(0.0f, 0.0f, 50.0f));
	}

	{
		static bool active = true;
		static D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 150.0f);
		if (DebugButton("PlayerBulletParticle"))
			SetPlayerBulletParticle(&pos, &active, &D3DXVECTOR3(-100.0f, 0.0f, 0.0f), &D3DXVECTOR3(100.0f, 0.0f, 0.0f));
	}

	//{
	//	DebugDrawTexture(renderTexture, 500.0f, 200.0f);
	//}

	EndDebugWindow("GameParticle");
}
#endif