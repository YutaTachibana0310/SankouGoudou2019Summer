//=====================================
//
//TutorialScene.cpp
//機能:チュートリアルシーン
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "TutorialScene.h"
#include "TutorialBG.h"

/**************************************
グローバル変数
***************************************/

/**************************************
初期化処理
***************************************/
void TutorialScene::Init()
{
	//インスタンス作成
	bg = new TutorialBG();

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
}

/**************************************
終了処理
***************************************/
void TutorialScene::Uninit()
{
	//インスタンス削除
	SAFE_DELETE(bg);

	//フォグを無効化
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->SetRenderState(D3DRS_FOGENABLE, false);
}

/**************************************
更新処理
***************************************/
void TutorialScene::Update(HWND hWnd)
{
	bg->Update();
}

/**************************************
描画処理
***************************************/
void TutorialScene::Draw()
{
	bg->Draw();
}
