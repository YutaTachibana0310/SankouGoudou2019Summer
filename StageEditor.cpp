//=====================================
//
//ステージエディタ処理[StageEditor.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "StageEditor.h"
#include "debugWindow.h"

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
コンストラクタ
***************************************/
StageEditor::StageEditor()
{
	windowContainer.resize(5);
	for (auto& window : windowContainer)
	{
		window = new BaseEditWindow();
	}
}

/**************************************
デストラクタ
***************************************/
StageEditor::~StageEditor()
{
	for (auto& window : windowContainer)
	{
		SAFE_DELETE(window)
	}
	windowContainer.clear();
}

/**************************************
初期化処理
***************************************/
void StageEditor::Init()
{

}

/**************************************
終了処理
***************************************/
void StageEditor::Uninit()
{

}

/**************************************
更新処理
***************************************/
void StageEditor::Update()
{

}

/**************************************
描画処理
***************************************/
void StageEditor::Draw()
{
	BeginDebugWindow("StageEditor");
	for (auto& window : windowContainer)
	{
		window->Draw();
		DebugNewLine();
	}
	EndDebugWindow("SageEditor");
}