//=====================================
//
//�x�[�X�G�f�B�b�g�E�B���h�E�w�b�_[BaseEditWindow.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _BASEEDITWINDOW_H_
#define _BASEEDITWINDOW_H_

#include "main.h"
#include "DataEditWindow.h"
#include <map>
#include "picojson\picojson.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class BaseEditWindow
{
public:
	BaseEditWindow();
	BaseEditWindow(int id, int frame, std::string type, picojson::object data);
	~BaseEditWindow();

	bool Draw();
	picojson::value Serialize();

	int id;
	int frame;
	std::string type;

private:

	std::map<std::string, DataEditWindow*> dataWindow;

	void CreateEditWindow();

	static UINT instanceCount;
};

#endif