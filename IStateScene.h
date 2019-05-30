//=====================================
//
//ステートシーンヘッダ[IStateScene.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _STATESCENE_H_
#define _STATESCENE_H_

#include "main.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class IStateScene
{
public:
	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	IStateScene() {};
	virtual ~IStateScene() {};
};

#endif