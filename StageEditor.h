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
#include <iterator>
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
	
	int selectedID;
	decltype(windowList)::iterator selectedData;

	LPDIRECT3DTEXTURE9 selectLine;
};

#endif