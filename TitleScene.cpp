//=====================================
//
//タイトルシーン処理[TitleScene.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "TitleScene.h"
#include "debugWindow.h"
#include "Game.h"
#include "InputController.h"
#include "TitleSceneUIManager.h"
#include "sound.h"
#include "InputController.h"
#include "BackGroundController.h"

/**************************************
マクロ定義
***************************************/

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/

/**************************************
初期化処理
***************************************/
void TitleScene::Init()
{
	//インスタンス作成
	titleSceneUIManager = new TitleSceneUIManager();
	bgController = new BackGroundController();

	titleSceneUIManager->Init();
	bgController->Init();

	bgController->transform.pos = D3DXVECTOR3(-8000.0, 0.0f, 12000.0f);
	bgController->transform.Rotate(-3.0f, 90.0f, 0.0f);

}

/**************************************
終了処理
***************************************/
void TitleScene::Uninit()
{
	titleSceneUIManager->Uninit();
	SAFE_DELETE(titleSceneUIManager);
	SAFE_DELETE(bgController);
}

/**************************************
更新処理
***************************************/
void TitleScene::Update(HWND hWnd)
{
	titleSceneUIManager->Update(hWnd);

	if (IsAnyKeyTriggered() || IsAnyButtonTriggerd())
	{
		//SE
		Sound::GetInstance()->SetPlaySE(ENTERSE, Sound::GetInstance()->enterSE, (Sound::GetInstance()->changevol / 5.0f));
		SceneChangeFlag(true, Scene::SceneGame);
	}

	bgController->Update();
}

/**************************************
描画処理
***************************************/
void TitleScene::Draw()
{
	bgController->Draw();
	titleSceneUIManager->Draw();
}