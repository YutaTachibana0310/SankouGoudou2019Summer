//=====================================
//
//Change�^�G�f�B�b�g�E�B���h�E�w�b�_[ChangeEditWindow.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _CHANGEEDITWINDOW_H_
#define _CHANGEEDITWINDOW_H_

#include "main.h"
#include "BaseEditWindow.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class ChangeEditWindow : public DataEditWindow
{
public:
	bool Draw();
	picojson::value Serialize();
	void Deserialize(picojson::object data);

	ChangeEditWindow() {}
	~ChangeEditWindow() {}

private:
	int start;
	int end;
};

#endif