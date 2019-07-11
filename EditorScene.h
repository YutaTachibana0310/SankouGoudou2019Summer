//=====================================
//
//エディタシーンヘッダ[EditorScene.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _EDITORSCENE_H_
#define _EDITORSCENE_H_

#include "main.h"
#include "IStateScene.h"

/**************************************
前方宣言
***************************************/
class EditorBG;
class StageEditor;

/**************************************
クラス定義
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

private:
	EditorBG * bg;
	StageEditor *editor;
};
#endif