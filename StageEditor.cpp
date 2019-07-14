//=====================================
//
//�X�e�[�W�G�f�B�^����[StageEditor.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "StageEditor.h"
#include "debugWindow.h"

#include "imgui\imgui.h"

#include <fstream>
#include <algorithm>

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
	selectedID = 0;
	selectedData = windowList.end();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Editor/selectLine.png", &selectLine);
}

/**************************************
�f�X�g���N�^
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
	windowList.sort([](BaseEditWindow* a, BaseEditWindow *b)
	{
		return a->frame < b->frame;
	});
}

/**************************************
�`�揈��
***************************************/
void StageEditor::Draw()
{
	BeginDebugWindow("StageEditor", true);

	//���j���[�o�[�̃A�C�e���ݒ�
	if (BeginMenuBar())
	{
		if (BeginMenuItem("File"))
		{
			//�Z�[�u�@�\
			MenuItem("Save", [&]()
			{
				Save();
			});

			//���[�h�@�\
			MenuItem("Load", [&]()
			{
				Load();
			});

			EndMenuItem();
		}
		EndMenuBar();
	}

	//�f�[�^�ǉ��@�\
	if (DebugButton("Add"))
	{
		windowList.push_back(new BaseEditWindow());
	}

	DebugSameLine();

	//�f�[�^�}���@�\
	if (DebugButton("Insert"))
	{
		windowList.insert(selectedData, new BaseEditWindow((*selectedData)));
	}

	//�I���f�[�^�폜�@�\
	if (DebugButton("Remove") && selectedData != windowList.end())
	{
		SAFE_DELETE(*selectedData);
		windowList.erase(selectedData);
		selectedData = windowList.begin();
	}
	
	DebugSameLine();

	//�f�[�^�폜�@�\
	if (DebugButton("Clear"))
	{
		for (auto& window : windowList)
		{
			SAFE_DELETE(window);
		}
		windowList.clear();
	}

	//�f�[�^�I���@�\
	DebugInputInt("Select ID", &selectedID);

	//�e�f�[�^�ݒ�E�B���h�E
	ImGui::BeginChild("##EditorChild", ImVec2(300, 850), ImGuiWindowFlags_NoTitleBar);
	for (auto itr = windowList.begin(); itr != windowList.end(); itr++)
	{
		//�I�𒆂̃f�[�^�Ȃ物�F�����C����\��
		if (selectedData == itr)
			DebugDrawTexture(selectLine, 300.0f, 2.0f);

		//�`�悵�ē��͂����o
		bool selected = (*itr)->Draw();
		if (selected)
			selectedData = itr;

		//���͂����o������I����Ԃ�
		if ((*itr)->id == selectedID)
			selectedData = itr;
	}
	ImGui::EndChild();

	EndDebugWindow("SageEditor");
}

/**************************************
�Z�[�u����
***************************************/
void StageEditor::Save()
{
	//�V���A���C�Y�pJSON�ϐ�
	picojson::object stageData;
	picojson::array dataList;

	//�e�f�[�^���V���A���C�Y
	for (auto& node : windowList)
	{
		dataList.push_back(node->Serialize());
	}

	//StageData�Ƃ��ăf�[�^�z����V���A���C�X
	stageData.emplace("StageData", picojson::value(dataList));
	std::string serializedData = picojson::value(stageData).serialize();

	//JSON�t�@�C���Ƃ��ďo��
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
	//�O�ׂ̈Ɍ��݂̃f�[�^���N���A
	for (auto& node : windowList)
	{
		SAFE_DELETE(node);
	}
	windowList.clear();

	//JSON�t�@�C����ǂݍ���
	std::ifstream ifs;
	ifs.open("data/JSON/test.json", std::ios::binary);

	picojson::value val;
	ifs >> val;
	ifs.close();

	//�e�f�[�^�����ꂼ��f�V���A���C�Y
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