//=====================================
//
//ステージエディタ処理[StageEditor.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "StageEditor.h"
#include "debugWindow.h"
#include <fstream>

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
	BeginDebugWindow("StageEditor", true);

	if (BeginMenuBar())
	{
		if (BeginMenuItem("File"))
		{
			MenuItem("Save", [&]()
			{
				Save();
			});

			MenuItem("Load", [&]()
			{

			});

			EndMenuItem();
		}
		EndMenuBar();
	}

	for (auto& window : windowContainer)
	{
		window->Draw();
		DebugNewLine();
	}
	EndDebugWindow("SageEditor");
}

/**************************************
セーブ処理
***************************************/
void StageEditor::Save()
{
	picojson::object stageData;
	picojson::array dataList;

	for (auto& node : windowContainer)
	{
		dataList.push_back(node->Serialize());
	}

	stageData.emplace("StageData", picojson::value(dataList));
	std::string serializedData = picojson::value(stageData).serialize();

	std::ofstream ofs;
	ofs.open("data/JSON/test.json", std::ios::out);
	ofs << serializedData << std::endl;
	ofs.close();
}