//=====================================
//
//�X�l�[�N�G�f�B�b�g�E�B���h�E�w�b�_[SnakeEditWindow.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _SNAKEEDITWINDOW_H_
#define _SNAKEEDITWINDOW_H_

#include "main.h"
#include "DataEditWindow.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class SnakeEditWindow : public DataEditWindow
{
public:
	SnakeEditWindow() {}
	~SnakeEditWindow() {}

	bool Draw();
	picojson::value Serialize();
	void Deserialize(picojson::object data);

private:
	std::vector<int> destList;
};

#endif