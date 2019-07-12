//=====================================
//
//ステージエディタ処理[StageEditor.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "StageEditor.h"
#include "debugWindow.h"

#include <fstream>
#include <algorithm>

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
	windowList.resize(5);
	for (auto& window : windowList)
	{
		window = new BaseEditWindow();
	}
}

/**************************************
デストラクタ
***************************************/
StageEditor::~StageEditor()
{
	for (auto& window : windowList)
	{
		SAFE_DELETE(window)
	}
	windowList.clear();
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
	windowList.sort([](BaseEditWindow* a, BaseEditWindow *b)
	{
		return a->frame < b->frame;
	});
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
				Load();
			});

			EndMenuItem();
		}
		EndMenuBar();
	}

	for (auto& window : windowList)
	{
		window->Draw();
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

	for (auto& node : windowList)
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

/**************************************
ロード処理
***************************************/
void StageEditor::Load()
{
	for (auto& node : windowList)
	{
		SAFE_DELETE(node);
	}
	windowList.clear();

	std::ifstream ifs;
	ifs.open("data/JSON/test.json", std::ios::binary);

	picojson::value val;
	ifs >> val;
	ifs.close();

	picojson::array& stageData = val.get<picojson::object>()["StageData"].get<picojson::array>();
	for (UINT i = 0; i < stageData.size(); i++)
	{
		picojson::object data = stageData[i].get<picojson::object>();
		
		int id = static_cast<int>(data["id"].get<double>());
		int frame = static_cast<int>(data["frame"].get<double>());
		std::string type = data["type"].get<std::string>();
		picojson::object obj = data["data"].get<picojson::object>();

		windowList.push_back(new BaseEditWindow(id, frame, type, obj));
	}
}