//=====================================
//
//�x�[�X�G�f�B�b�g�E�B���h�E����[BaseEditWindow.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "BaseEditWindow.h"
#include "debugWindow.h"
#include "ChangeEditWindow.h"

#include <algorithm>

using namespace std;

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/

/**************************************
static�ϐ�
***************************************/
UINT BaseEditWindow::instanceCount;

/**************************************
�R���X�g���N�^
***************************************/
BaseEditWindow::BaseEditWindow()
{
	id = instanceCount++;
	frame = 0;
	CreateEditWindow();
}

/**************************************
�R���X�g���N�^
***************************************/
BaseEditWindow::BaseEditWindow(int id, int frame, std::string type, picojson::object data)
{
	this->id = id;
	this->frame = frame;
	this->type = type;

	CreateEditWindow();
	dataWindow[type]->Deserialize(data);

	instanceCount++;
}

/**************************************
�f�X�g���N�^
***************************************/
BaseEditWindow::~BaseEditWindow()
{
	instanceCount--;
	for (auto pair : dataWindow)
	{
		SAFE_DELETE(pair.second);
	}
	dataWindow.clear();

}
/**************************************
�`�揈��
***************************************/
void BaseEditWindow::Draw()
{
	DebugTreeExpansion(true);
	if (DebugTreePush(to_string(id).c_str()))
	{
		string windowName = to_string(id);

		string frameLabel = string("frame");
		DebugInputInt(frameLabel.c_str(), &frame);

		string typeName = string("type");
		DebugInputText(typeName.c_str(), &type);

		if (dataWindow.count(type) != 0)
		{
			dataWindow[type]->Draw(id);
		}

		DebugTreePop();
	}
}

/**************************************
�V���A���C�Y����
***************************************/
picojson::value BaseEditWindow::Serialize()
{
	picojson::object obj;

	obj.emplace(make_pair("id", picojson::value((double)id)));
	obj.emplace(make_pair("frame", picojson::value((double)frame)));
	obj.emplace(make_pair("type", picojson::value(type)));

	if (dataWindow.count(type) != 0)
	{
		obj.emplace(make_pair("data", dataWindow[type]->Serialize()));
	}

	return picojson::value(obj);
}

/**************************************
�G�f�B�b�g�E�B���h�E�쐬����
***************************************/
void BaseEditWindow::CreateEditWindow()
{
	dataWindow["Change"] = new ChangeEditWindow();
}