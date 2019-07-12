//=====================================
//
//�X�e�[�W�G�f�B�^�w�b�_[StageEditor.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _STAGEEDITOR_H_
#define _STAGEEDITOR_H_

#include "main.h"
#include <list>
#include "BaseEditWindow.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class StageEditor
{
public:
	StageEditor();
	~StageEditor();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void Save();
	void Load();

private:
	std::list<BaseEditWindow*> windowList;

};

#endif