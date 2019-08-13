//=====================================
//
//�x�[�X�G�f�B�b�g�E�B���h�E����[BaseEditWindow.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "BaseEditWindow.h"
#include "debugWindow.h"
#include "ChangeEditWindow.h"
#include "SnakeEditWindow.h"

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
�R���X�g���N�^
***************************************/
BaseEditWindow::BaseEditWindow(BaseEditWindow *src)
{
	id = instanceCount++;
	frame = src->frame;
	type = src->type;

	CreateEditWindow();
}

/**************************************
�f�X�g���N�^
***************************************/
BaseEditWindow::~BaseEditWindow()
{
	for (auto pair : dataWindow)
	{
		SAFE_DELETE(pair.second);
	}
	dataWindow.clear();

}
/**************************************
�`�揈��
***************************************/
bool BaseEditWindow::Draw()
{
	bool selected = false;

	DebugTreeExpansion(true);
	if (DebugTreePush((string("id") + to_string(id)).c_str()))
	{
		string windowName = to_string(id);

		string frameLabel = string("frame");
		selected |= DebugInputInt(frameLabel.c_str(), &frame);

		string typeName = string("type");
		selected |= DebugInputText(typeName.c_str(), &type);

		if (dataWindow.count(type) != 0)
		{
			selected |= dataWindow[type]->Draw();
		}

		DebugTreePop();
	}

	return selected;
}

/**************************************
�V���A���C�Y����
***************************************/
picojson::value BaseEditWindow::Serialize(int& sumFrame)
{
	picojson::object obj;

	sumFrame += frame;

	obj.emplace(make_pair("id", picojson::value((double)id)));
	obj.emplace(make_pair("frame", picojson::value((double)(sumFrame))));
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
	dataWindow["Straight"] = new ChangeEditWindow();
	dataWindow["Snake"] = new SnakeEditWindow();
}