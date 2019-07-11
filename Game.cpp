//=====================================
//
//ゲーム処理[Game.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "Game.h"
#include "input.h"
#include "light.h"
#include "camera.h"
#include "debugWindow.h"
#include "debugTimer.h"
#include "sound.h"
#include "masktex.h"
#include "Framework\ResourceManager.h"

#include "IStateScene.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "ResultScene.h"
#include "EditorScene.h"
#include "InputController.h"

#include "SoundStateScene.h"
#include "SoundTitleScene.h"
#include "SoundGameScene.h"
#include "SoundResultScene.h"

/**************************************
マクロ定義
***************************************/

/**************************************
プロトタイプ宣言
***************************************/
void CreateScreenVertexBuffer();
void CreateRenderTarget();

/**************************************
グローバル変数
***************************************/
//変更後のビューポート
static D3DVIEWPORT9 viewPort;

//描画用テクスチャ&サーフェイス
static LPDIRECT3DTEXTURE9 renderTexture;
static LPDIRECT3DSURFACE9 renderSurface;

//Zマップ用テクスチャ&サーフェイス
static LPDIRECT3DTEXTURE9 zMapTexture;
static LPDIRECT3DSURFACE9 zMapSurface;

//バックバッファへ描画するための頂点バッファ
static LPDIRECT3DVERTEXBUFFER9 screenVtx;

//シーン管理のステートマシン
static IStateScene* fsm[SceneMax];
static SoundStateScene* ssm[SceneMax];

//現在のシーン
static Scene currentScene = SceneTitle;

/**************************************
初期化処理
***************************************/
void InitGame(HINSTANCE hInstance, HWND hWnd)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	CreateScreenVertexBuffer();
	CreateRenderTarget();

	InitInput(hInstance, hWnd);
	InitCamera();
	InitLight();
	InitDebugWindow(hWnd, pDevice);
	InitMask(MASK_SIZE, MASK_SIZE, 0);

	//ステートマシンに各シーンを追加
	fsm[SceneTitle] = new TitleScene();
	fsm[SceneGame] = new GameScene();
	fsm[SceneResult] = new ResultScene();
	fsm[SceneEditor] = new EditorScene();

	ssm[SceneTitle] = new SoundTitleScene();
	ssm[SceneGame] = new SoundGameScene();
	ssm[SceneResult] = new SoundResultScene();

	RegisterDebugTimer("Main");

	fsm[currentScene]->Init();
}

/**************************************
終了処理
***************************************/
void UninitGame()
{
	UninitInput();
	UninitLight();
	UninitDebugWindow(0);
	UninitDebugTimer();
	UninitMask();

	fsm[currentScene]->Uninit();
}

/**************************************
更新処理
***************************************/
void UpdateGame(HWND hWnd)
{
	//testのため毎回ゲームシーンを呼び出す
	MaskRun(SceneGame);
	UpdateMask();

	//念のためサウンドを最初に（渡邉）
	if (ssm[currentScene] != nullptr)
	{
		Sound::GetInstance()->run();
		ssm[currentScene]->Play();
	}

	UpdateDebugWindow();
	UpdateInput();
	UpdateLight();
	UpdateCamera();

	fsm[currentScene]->Update(hWnd);
}

/**************************************
描画処理
***************************************/
void DrawGame()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//現在のビューポートを退避してレンダーターゲットを切り替え
	D3DVIEWPORT9 oldVirwPort;
	pDevice->GetViewport(&oldVirwPort);

	//バックバッファを退避してレンダーターゲットを切り替え
	LPDIRECT3DSURFACE9 oldSuf;
	pDevice->GetRenderTarget(0, &oldSuf);
	pDevice->SetRenderTarget(0, renderSurface);
	pDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), 0, 1.0f, 0);

	//マスクセット
	DrawMaskTexSet();

	//オブジェクトを描画
	SetCamera();

	fsm[currentScene]->Draw();

	//マスク終了
	DrawMaskTexEnd();

	//結果をバックバッファへと描画
	pDevice->SetViewport(&oldVirwPort);
	pDevice->SetRenderTarget(0, oldSuf);
	SAFE_RELEASE(oldSuf);

	pDevice->SetTexture(0, renderTexture);
	pDevice->SetStreamSource(0, screenVtx, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	//FPS表示
#ifdef _DEBUG
	DebugLog("FPS:%d", GetCurrentFPS());
#endif

	DrawDebugWindow();
}

/**************************************
描画用頂点バッファ作成
***************************************/
void CreateScreenVertexBuffer()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&screenVtx,
		0);

	VERTEX_2D *pVtx;
	screenVtx->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].vtx = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].vtx = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].vtx = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx[0].rhw =
		pVtx[1].rhw =
		pVtx[2].rhw =
		pVtx[3].rhw = 1.0f;

	pVtx[0].diffuse =
		pVtx[1].diffuse =
		pVtx[2].diffuse =
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	screenVtx->Unlock();
}

/**************************************
レンダーターゲット作成
***************************************/
void CreateRenderTarget()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//レンダーテクスチャ作成
	pDevice->CreateTexture(SCREEN_WIDTH,
		SCREEN_HEIGHT,
		1,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_X8R8G8B8,
		D3DPOOL_DEFAULT,
		&renderTexture,
		0);

	renderTexture->GetSurfaceLevel(0, &renderSurface);

	//Zバッファ作成

	//ビューポート作成
	viewPort.Height = 2048;
	viewPort.Width = 2048;
	viewPort.MinZ = 0.0f;
	viewPort.MaxZ = 1.0f;
	viewPort.X = 0;
	viewPort.Y = 0;
}
/*************************************************************************
シーン変更処理(渡邉マスク用）
シーン切り替え時はMaskRunの引数に次のシーンを指定
ChangeSceneへはMaskRunを実行すると呼び出されます
**************************************************************************/
void MaskRun(Scene next) {

	////現在テスト用でエンターキーで切り替え
	//if (GetKeyboardTrigger(DIK_RETURN)) {

	//	SceneChangeFlag(true, next);

	//}

}
/**************************************
シーン変更処理
***************************************/
void ChangeScene(Scene next)
{
	fsm[currentScene]->Uninit();
	ResourceManager::Instance()->AllRelease();

	if (ssm[currentScene] != NULL)
		ssm[currentScene]->Stop();

	currentScene = next;

	fsm[currentScene]->Init();
	Sound::GetInstance()->Sound::Sound();

}

/**************************************
レンダーターゲット作成
***************************************/
LPDIRECT3DTEXTURE9 GetDrawDataTemp()
{
	return renderTexture;
}

