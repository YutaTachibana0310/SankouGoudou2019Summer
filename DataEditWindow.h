//=====================================
//
//�f�[�^�G�f�B�b�g�E�B���h�E�w�b�_[DataEditWindow.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _DATAEDITWINDOW_H_
#define _DATAEDITWINDOW_H_

#include "main.h"
#include "picojson\picojson.h"

/**************************************
�}�N����`
***************************************/

/**************************************
DataEditWindow�N���X
�p�����Draw(), Serialize()����������
***************************************/
class DataEditWindow
{
public:
	DataEditWindow() {}
	virtual ~DataEditWindow() {}

	virtual bool Draw() = 0;
	virtual picojson::value Serialize() = 0;
	virtual void Deserialize(picojson::object data) = 0;
};

#endif