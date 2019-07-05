//=====================================
//
//ゲームパーティクルマネージャ処理[GameParticleManager.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "GameParticleManager.h"

#include <vector>

#include "ScoreParticleController.h"
#include "PlayerBulletParticleController.h"
#include "PlayerTrailParticleController.h"
#include "EnemyExplosionController.h"

#include "PostEffect\ScreenObject.h"
#include "PostEffect\CrossFilterController.h"

using namespace std;

/**************************************
マクロ定義
***************************************/
#define GAMEPARTICLE_USE_DEBUG

#ifdef GAMEPARTICLE_USE_DEBUG
#include "debugWindow.h"
#endif

/**************************************
構造体定義
***************************************/
enum ParticleController
{
	ScoreParticle,
	PlayerBulletParticle,
	PlayerTrailParticle,
	EnemyExplosion,
	ControllerMax
};

/**************************************
グローバル変数
***************************************/
//レンダーターゲット関連
static LPDIRECT3DTEXTURE9 renderTexture;
static LPDIRECT3DSURFACE9 renderSurface;
static D3DVIEWPORT9 viewPort;
static ScreenObject *screenObj;

vector<BaseParticleController*> container;

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

	//各コントローラを生成
	container.resize(ControllerMax);
	container[ScoreParticle] = new ScoreParticleController();
	container[PlayerBulletParticle] = new PlayerBulletParticleController();
	container[PlayerTrailParticle] = new PlayerTrailParticleController();
	container[EnemyExplosion] = new EnemyExplosionController();

	//レンダーターゲット作成
	GameParticle::CreateRenderTarget();

	//各パーティクル初期化
	for (BaseParticleController *itr : container)
	{
		itr->Init();
	}
}

/**************************************
終了処理
***************************************/
void UninitGameParticleManager(int num)
{
	for (BaseParticleController *itr : container)
	{
		itr->Uninit();
	}

	vector<BaseParticleController*>().swap(container);

	SAFE_RELEASE(renderSurface);
	SAFE_RELEASE(renderTexture);
	SAFE_DELETE(screenObj);
}

/**************************************
更新処理
***************************************/
void UpdateGameParticleManager(void)
{
#ifdef GAMEPARTICLE_USE_DEBUG
	GameParticle::DrawDebugWindow();
#endif

	for (BaseParticleController *itr : container)
	{
		itr->Update();
	}
}

/**************************************
描画処理
***************************************/
void DrawGameParticleManager(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	////レンダリング設定切り替え
	D3DVIEWPORT9 oldViewport;
	LPDIRECT3DSURFACE9 oldSuf;
	pDevice->GetViewport(&oldViewport);
	pDevice->GetRenderTarget(0, &oldSuf);
	GameParticle::ChangeRenderParameter();

	BaseParticleController::BeginDraw();

	//描画
	bool isDrewd = false;
	for (auto itr = container.begin(); itr != container.end(); itr++)
	{
		isDrewd |= (*itr)->Draw();
	}

	BaseParticleController::EndDraw();

#ifndef _DEBUG	//クロスフィルタはRelease版でのみ適用する
	//ポストエフェクト
	if(isDrewd)
		CrossFilterController::Instance()->Draw(renderTexture);
#endif // !_DEBUG

	////全ての結果を元のレンダーターゲットに描画
	GameParticle::RestoreRenderParameter(oldSuf, oldViewport);
	screenObj->Draw();

	//レンダーステート復元
	pDevice->SetRenderState(D3DRS_LIGHTING, true);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

/**************************************
スコアパーティクル発生処理
***************************************/
void SetScoreParticle(D3DXVECTOR3 *pos)
{
	container[ScoreParticle]->SetEmitter(pos);
}

/**************************************
スコアパーティクル発生処理
***************************************/

/**************************************
プレイヤーバレットセット処理
***************************************/
void SetPlayerBulletParticle(D3DXVECTOR3 *pPos, bool *pActive, D3DXVECTOR3 *edgeRight, D3DXVECTOR3 *edgeLeft)
{
	PlayerBulletParticleController *controller
		= static_cast<PlayerBulletParticleController*>(container[PlayerBulletParticle]);

	controller->SetEmitter(pPos, pActive, edgeRight, edgeLeft);
}

/**************************************
プレイヤートレイルパーティクル処理
***************************************/
void SetPlayerTrailParticle(D3DXVECTOR3 *pPos, bool *pActive)
{
	PlayerTrailParticleController *controller =
		static_cast<PlayerTrailParticleController*>(container[PlayerTrailParticle]);

	controller->SetEmitter(pPos, pActive);
}

/**************************************
エネミーエクスプロージョン処理
***************************************/
void SetEnemyExplosion(D3DXVECTOR3 *pos)
{
	EnemyExplosionController *controller =
		static_cast<EnemyExplosionController*>(container[EnemyExplosion]);

	controller->SetEmitter(pos);
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

#ifdef GAMEPARTICLE_USE_DEBUG
/**************************************
デバッグウィンドウ
***************************************/
void GameParticle::DrawDebugWindow(void)
{
	BeginDebugWindow("GameParticle");

	{
		if (DebugButton("ScoreParticle"))
			container[0]->SetEmitter(&D3DXVECTOR3(0.0f, 0.0f, 50.0f));
	}

	{
		if (DebugButton("EnemyExplosion"))
			container[EnemyExplosion]->SetEmitter(&D3DXVECTOR3(0.0f, 0.0f, 100.0f));
	}
	EndDebugWindow("GameParticle");
}
#endif