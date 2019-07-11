//=====================================
//
//�X�e�[�W�G�f�B�^����[StageEditor.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "StageEditor.h"
#include "debugWindow.h"
#include <fstream>

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�R���X�g���N�^
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
�f�X�g���N�^
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
����������
***************************************/
void StageEditor::Init()
{

}

/**************************************
�I������
***************************************/
void StageEditor::Uninit()
{

}

/**************************************
�X�V����
***************************************/
void StageEditor::Update()
{

}

/**************************************
�`�揈��
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

	for (auto& window : windowContainer)
	{
		window->Draw();
		DebugNewLine();
	}
	EndDebugWindow("SageEditor");
}

/**************************************
�Z�[�u����
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

/**************************************
���[�h����
***************************************/
void StageEditor::Load()
{
	for (auto& node : windowContainer)
	{
		SAFE_DELETE(node);
	}
	windowContainer.clear();

	std::ifstream ifs;
	ifs.open("data/JSON/test.json", std::ios::binary);

	picojson::value val;
	ifs >> val;
	ifs.close();

	picojson::array& stageData = val.get<picojson::object>()["StageData"].get<picojson::array>();
	windowContainer.resize(stageData.size());
	for (int i = 0; i < stageData.size(); i++)
	{
		picojson::object data = stageData[i].get<picojson::object>();
		
		int id = static_cast<int>(data["id"].get<double>());
		int frame = static_cast<int>(data["frame"].get<double>());
		std::string type = data["type"].get<std::string>();
		picojson::object obj = data["data"].get<picojson::object>();

		windowContainer[i] = new BaseEditWindow(id, frame, type, obj);
	}
}