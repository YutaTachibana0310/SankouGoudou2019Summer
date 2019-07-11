//=====================================
//
//�x�[�X�G�f�B�b�g�E�B���h�E����[BaseEditWindow.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "BaseEditWindow.h"
#include "debugWindow.h"
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
	BeginDebugWindow(windowName.c_str());

	DebugInputInt("frame", &frame);
	DebugInputText("type", &type);

	if (dataWindow.count(type) != 0)
	{
		dataWindow[type]->Draw();
	}

	EndDebugWindow(windowName.c_str());
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