//=====================================
//
//MidiumEditWindow.h
//�@�\:���^�G�l�~�[�̏o���f�[�^�G�f�B�^
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _MIDIUMEDITWINDOW_H_
#define _MIDIUMEDITWINDOW_H_

#include "main.h"
#include "BaseEditWindow.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class MidiumEditWindow : public DataEditWindow
{
	using DataEditWindow::DataEditWindow;
public:
	bool Draw();
	picojson::value Serialize();
	void Deserialize(picojson::object data);

private:
	std::vector<int> startList;
	std::vector<int> goalList;
};
#endif