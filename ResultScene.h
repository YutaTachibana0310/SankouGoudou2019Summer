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

/**************************************
クラス定義
***************************************/
class ResultScene : public IStateScene
{
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	ResultScene() {}
	~ResultScene() {}
};

#endif