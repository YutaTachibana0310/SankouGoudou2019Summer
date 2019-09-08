//=====================================
//
//TutorialScene.cpp
//機能:チュートリアルシーン
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "TutorialScene.h"
#include "TutorialBG.h"
#include "GameSceneUIManager.h"
#include "PlayerObserver.h"
#include "PlayerController.h"
#include "InputController.h"
#include "GameParticleManager.h"
#include "TutorialController.h"

/**************************************
グローバル変数
***************************************/

/**************************************
初期化処理
***************************************/
void TutorialScene::Init()
{
	//UIインスタンス作成
	container = new GameSceneUIManager();

	//☆ボタンの位置からワールド座標を計算
	std::vector<D3DXVECTOR3> starPositionContainer;
	container->GetStarPosition(starPositionContainer);
	LineTrailModel::CalcEdgePosition(starPositionContainer);

	//他のインスタンス作成
	bg = new TutorialBG();
	playerObserver = new PlayerObserver();
	controller = new TutorialController();

	//PlayerControllerにPlayerObserverをセット
	SetPlayerObserverAdr(playerObserver);

	//インプットコントローラにUIManagerのインスタンスを渡す
	SetInstanceUIManager(container);
	
	//フォグを有効化
	FLOAT StartPos = 10000;
	FLOAT EndPos = 50000;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->SetRenderState(D3DRS_FOGENABLE, true);
	pDevice->SetRenderState(D3DRS_FOGCOLOR, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	pDevice->SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_NONE);
	pDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);
	pDevice->SetRenderState(D3DRS_FOGSTART, *(DWORD*)(&StartPos));
	pDevice->SetRenderState(D3DRS_FOGEND, *(DWORD*)(&EndPos));

	//初期化処理
	GameParticleManager::Instance()->Init();
	playerObserver->Init();
}

/**************************************
終了処理
***************************************/
void TutorialScene::Uninit()
{
	//インスタンス削除
	SAFE_DELETE(bg);
	SAFE_DELETE(container);
	SAFE_DELETE(controller);

	//フォグを無効化
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	if(pDevice != NULL)
		pDevice->SetRenderState(D3DRS_FOGENABLE, false);
}

/**************************************
更新処理
***************************************/
void TutorialScene::Update(HWND hWnd)
{
	//入力確認
	playerObserver->CheckInput();

	bg->Update();
	playerObserver->Update();

	controller->Update();

	container->Update(hWnd);

	GameParticleManager::Instance()->Update();
}

/**************************************
描画処理
***************************************/
void TutorialScene::Draw()
{
	bg->Draw();
	playerObserver->Draw();

	GameParticleManager::Instance()->Draw();

	container->Draw();

	controller->Draw();
}
