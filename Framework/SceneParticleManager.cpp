//=====================================
//
//シーンパーティクルマネージャ処理[SceneParticleManager.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "SceneParticleManager.h"
#include "../PostEffect/CrossFilterController.h"
#include "../debugTimer.h"

/**************************************
マクロ定義
***************************************/
#define SCENEMPARTICLEMANAGER_LABEL		"ParticleManager"

/**************************************
コンストラクタ
***************************************/
SceneParticleManager::SceneParticleManager()
{
	RegisterDebugTimer(SCENEMPARTICLEMANAGER_LABEL);
}

/**************************************
デストラクタ
***************************************/
SceneParticleManager::~SceneParticleManager()
{

}

/**************************************
初期化処理
***************************************/
void SceneParticleManager::Init()
{
	//シングルトン化のため、ここでリソースを作成
	if (!initialized)
	{
		CreateRenderTarget();
		initialized = true;
	}
}

/**************************************
終了処理
***************************************/
void SceneParticleManager::Uninit()
{
	for (auto& controller : controllers)
	{
		controller->Uninit();
	}

	//シングルトンのためここでリソース解放
	SAFE_RELEASE(renderSurface);
	SAFE_RELEASE(renderTexture);
	SAFE_DELETE(screenObj);

	for (auto& controller : controllers)
	{
		SAFE_DELETE(controller);
	}
	controllers.clear();

	initialized = false;
}

/**************************************
更新処理
***************************************/
void SceneParticleManager::Update()
{
	CountDebugTimer(SCENEMPARTICLEMANAGER_LABEL, "Update");
	for (auto& controller : controllers)
	{
		controller->Update();
	}
	CountDebugTimer(SCENEMPARTICLEMANAGER_LABEL, "Update");
}

/**************************************
描画処理
***************************************/
void SceneParticleManager::Draw()
{
	//レンダーパラメータ切り替え
	ChangeRenderParameter();

	//インスタンシング描画開始
	BaseParticleController::BeginDraw();

	//描画
	CountDebugTimer(SCENEMPARTICLEMANAGER_LABEL, "Draw");
	bool isDrewd = false;
	for (auto& controller : controllers)
	{
		isDrewd |= controller->Draw();
	}
	CountDebugTimer(SCENEMPARTICLEMANAGER_LABEL, "Draw");

	//インスタンシング描画終了
	BaseParticleController::EndDraw();

	//リリース版のみクロスフィルタを適用する
#ifndef _DEBUG	
	CountDebugTimer(SCENEMPARTICLEMANAGER_LABEL, "PostEffect");
	if (isDrewd)
		CrossFilterController::Instance()->Draw(renderTexture);
	CountDebugTimer(SCENEMPARTICLEMANAGER_LABEL, "PostEffect");
#endif

	//すべての結果を元のレンダーターゲットに描画
	CountDebugTimer(SCENEMPARTICLEMANAGER_LABEL, "Render");
	RestoreRenderParameter();
	screenObj->Draw();
	CountDebugTimer(SCENEMPARTICLEMANAGER_LABEL, "Render");

	//レンダーステート復元
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->SetRenderState(D3DRS_LIGHTING, true);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	DrawDebugTimer(SCENEMPARTICLEMANAGER_LABEL);

}

/**************************************
レンダーターゲット作成処理
***************************************/
void SceneParticleManager::CreateRenderTarget()
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
レンダーパラメータ変更処理
***************************************/
void SceneParticleManager::ChangeRenderParameter()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//レンダーターゲットとビューポートをキャッシュ
	pDevice->GetRenderTarget(0, &oldSuf);
	pDevice->GetViewport(&oldViewport);

	//レンダーターゲット切り替え
	pDevice->SetRenderTarget(0, renderSurface);
	pDevice->SetViewport(&viewPort);
	pDevice->Clear(0, 0, D3DCLEAR_TARGET, 0, 0.0f, 0);
}

/**************************************
レンダーパラメータ復元処理
***************************************/
void SceneParticleManager::RestoreRenderParameter()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderTarget(0, oldSuf);
	pDevice->SetTexture(0, renderTexture);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	pDevice->SetViewport(&oldViewport);
	SAFE_RELEASE(oldSuf);
}