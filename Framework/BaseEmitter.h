//=====================================
//
//テンプレートヘッダ[BaseEmitter.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BASEEMITTER_H_
#define _BASEEMITTER_H_

#include "../main.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class BaseEmitter
{
public:
	BaseEmitter();
	virtual ~BaseEmitter();

	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;

	bool IsActive();

	Transform transform;

protected:
	bool active;
	int cntFrame;
	int duration;
};

#endif