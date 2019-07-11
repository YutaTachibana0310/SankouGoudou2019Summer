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
	
	dataWindow["Change"] = new ChangeEditWindow();
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
	string windowName = to_string(id);

	string frameLabel = string("frame") + to_string(id);
	DebugInputInt(frameLabel.c_str(), &frame);

	string typeName = string("type") + to_string(id);
	DebugInputText(typeName.c_str(), &type);

	if (dataWindow.count(type) != 0)
	{
		dataWindow[type]->Draw(id);
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

	if (dataWindow.count(type) != 0)
	{
		obj.emplace(make_pair("data", dataWindow[type]->Serialize()));
	}

	return picojson::value(obj);
}