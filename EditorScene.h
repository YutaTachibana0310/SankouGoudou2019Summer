//=====================================
//
//�G�f�B�^�V�[���w�b�_[EditorScene.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _EDITORSCENE_H_
#define _EDITORSCENE_H_

#include "main.h"
#include "IStateScene.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class EditorScene : public IStateScene
{
public:
	void Init();
	void Uninit();
	void Update(HWND hWnd);
	void Draw();

	EditorScene() {}
	~EditorScene() {}
};
#endif