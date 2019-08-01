//=============================================================================
//
// ResultシーンUI管理処理 [ResultSceneUIMaager.h]
// Author : 
//
//=============================================================================
#ifndef _RESULTSCENEUIMANAGER_H_
#define _RESULTSCENEUIMANAGER_H_

#include "UIdrawer.h"

/**************************************
前方宣言
***************************************/
class Object;
class ResultBG;

/**************************************
構造体定義
***************************************/
class ResultSceneUI:public Object
{
public:
	ResultBG *resultBG;
	virtual void Init(void);
	virtual void Uninit(void);
	virtual void Update(HWND hwnd);
	virtual void Draw(void);
};

#endif
