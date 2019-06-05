//=====================================
//
//タイトルシーンヘッダ[TitleScene.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _TITLESCENE_H_
#define _TITLESCENE_H_

#include "main.h"
#include "IStateScene.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class TitleScene : public IStateScene
{
public:
	void Init();
	void Uninit();
	void Update(HWND hWnd);
	void Draw();

	TitleScene() {};
	~TitleScene() {};
};

#endif