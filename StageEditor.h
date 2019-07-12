//=====================================
//
//ステージエディタヘッダ[StageEditor.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _STAGEEDITOR_H_
#define _STAGEEDITOR_H_

#include "main.h"
#include <list>
#include "BaseEditWindow.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
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