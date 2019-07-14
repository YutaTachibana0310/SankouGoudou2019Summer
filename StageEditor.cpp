//=====================================
//
//ステージエディタ処理[StageEditor.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "StageEditor.h"
#include "debugWindow.h"

#include "imgui\imgui.h"

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
	selectedID = 0;
	selectedData = windowList.end();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Editor/selectLine.png", &selectLine);
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

	SAFE_RELEASE(selectLine);
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

	//メニューバーのアイテム設定
	if (BeginMenuBar())
	{
		if (BeginMenuItem("File"))
		{
			//セーブ機能
			MenuItem("Save", [&]()
			{
				Save();
			});

			//ロード機能
			MenuItem("Load", [&]()
			{
				Load();
			});

			EndMenuItem();
		}
		EndMenuBar();
	}

	//データ追加機能
	if (DebugButton("Add"))
	{
		windowList.push_back(new BaseEditWindow());
	}

	DebugSameLine();

	//データ挿入機能
	if (DebugButton("Insert"))
	{
		windowList.insert(selectedData, new BaseEditWindow((*selectedData)));
	}

	//選択データ削除機能
	if (DebugButton("Remove") && selectedData != windowList.end())
	{
		SAFE_DELETE(*selectedData);
		windowList.erase(selectedData);
		selectedData = windowList.begin();
	}
	
	DebugSameLine();

	//データ削除機能
	if (DebugButton("Clear"))
	{
		for (auto& window : windowList)
		{
			SAFE_DELETE(window);
		}
		windowList.clear();
	}

	//データ選択機能
	DebugInputInt("Select ID", &selectedID);

	//各データ設定ウィンドウ
	ImGui::BeginChild("##EditorChild", ImVec2(300, 850), ImGuiWindowFlags_NoTitleBar);
	for (auto itr = windowList.begin(); itr != windowList.end(); itr++)
	{
		//選択中のデータなら黄色いラインを表示
		if (selectedData == itr)
			DebugDrawTexture(selectLine, 300.0f, 2.0f);

		//描画して入力を検出
		bool selected = (*itr)->Draw();
		if (selected)
			selectedData = itr;

		//入力を検出したら選択状態に
		if ((*itr)->id == selectedID)
			selectedData = itr;
	}
	ImGui::EndChild();

	EndDebugWindow("SageEditor");
}

/**************************************
セーブ処理
***************************************/
void StageEditor::Save()
{
	//シリアライズ用JSON変数
	picojson::object stageData;
	picojson::array dataList;

	//各データをシリアライズ
	for (auto& node : windowList)
	{
		dataList.push_back(node->Serialize());
	}

	//StageDataとしてデータ配列をシリアライス
	stageData.emplace("StageData", picojson::value(dataList));
	std::string serializedData = picojson::value(stageData).serialize();

	//JSONファイルとして出力
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
	//念の為に現在のデータをクリア
	for (auto& node : windowList)
	{
		SAFE_DELETE(node);
	}
	windowList.clear();

	//JSONファイルを読み込み
	std::ifstream ifs;
	ifs.open("data/JSON/test.json", std::ios::binary);

	picojson::value val;
	ifs >> val;
	ifs.close();

	//各データをそれぞれデシリアライズ
	picojson::array& stageData = val.get<picojson::object>()["StageData"].get<picojson::array>();
	for (UINT i = 0; i < stageData.size(); i++)
	{
		picojson::object data = stageData[i].get<picojson::object>();

		int frame = static_cast<int>(data["frame"].get<double>());
		std::string type = data["type"].get<std::string>();
		picojson::object obj = data["data"].get<picojson::object>();

		windowList.push_back(new BaseEditWindow(i, frame, type, obj));
	}
}