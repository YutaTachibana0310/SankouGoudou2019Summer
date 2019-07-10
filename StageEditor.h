//=====================================
//
//ステージエディタヘッダ[StageEditor.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _STAGEEDITOR_H_
#define _STAGEEDITOR_H_

#include "main.h"
#include <vector>

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

private:
};

#endif