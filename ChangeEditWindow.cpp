//=====================================
//
//Change�^�G�f�B�b�g�E�B���h�E����[ChangeEditWIndow.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "ChangeEditWindow.h"
#include "debugWindow.h"

using namespace std;

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/

/**************************************
�`�揈��
***************************************/
void ChangeEditWindow::Draw(UINT id)
{
	string startLabel = string("start") + to_string(id);
	DebugInputInt(startLabel.c_str(), &start);

	string endLabel = string("end") + to_string(id);
	DebugInputInt(endLabel.c_str(), &end);

	start = Clamp(0, 5, start);
	end = Clamp(0, 5, end);
}

/**************************************
�V���A���C�Y����
***************************************/
picojson::value ChangeEditWindow::Serialize()
{
	picojson::object obj;
	obj.emplace(make_pair("start", picojson::value((double)start)));
	obj.emplace(make_pair("end", picojson::value((double)end)));

	return picojson::value(obj);
}

/**************************************
�f�V���A���C�Y����
***************************************/
void ChangeEditWindow::Deserialize(picojson::object data)
{
	this->start = static_cast<int>(data["start"].get<double>());
	this->end = static_cast<int>(data["end"].get<double>());
}