//=====================================
//
//リザルトシーンヘッダ[ResultScene.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _RESULTSCENE_H_
#define _RESULTSCENE_H_

#include "main.h"
#include "IStateScene.h"

/**************************************
マクロ定義
***************************************/
class ResultPlayer;

/**************************************
クラス定義
***************************************/
class ResultScene : public IStateScene
{
public:
	void Init();
	void Uninit();
	void Update(HWND hWnd);
	void Draw();

	ResultScene() {}
	~ResultScene() {}

private:
	ResultPlayer *player;
};

#endif