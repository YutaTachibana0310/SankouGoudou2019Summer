//=====================================
//
//リザルトシーン処理[ResultScene.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "ResultScene.h"
#include "debugWindow.h"
#include "Game.h"
#include "ResultSceneUIManager.h"
#include "ResultPlayer.h"
#include "Framework\PlayerPrefs.h"
#include "sound.h"

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
void ResultScene::Init()
{
	bool gameresult = PlayerPrefs::GetBool("GameResult");
	player = new ResultPlayer(gameresult);

	InitResultSceneUI();

	if (gameresult) {
		Sound::GetInstance()->SetPlaySE(RESULTCLEAR, true, (Sound::GetInstance()->changevol / 10.0f));
	}
	else {
		Sound::GetInstance()->SetPlaySE(RESULTFAILED, true, (Sound::GetInstance()->changevol / 10.0f));
	}

}

/**************************************
終了処理
***************************************/
void ResultScene::Uninit()
{
	UninitResultSceneUI();

	SAFE_DELETE(player);
}

/**************************************
更新処理
***************************************/
void ResultScene::Update(HWND hWnd)
{
	player->Update();
	UpdateResultSceneUI(hWnd);
}

/**************************************
描画処理
***************************************/
void ResultScene::Draw()
{
	DrawResultSceneBG();
	player->Draw();
	DrawResultSceneUI();
}