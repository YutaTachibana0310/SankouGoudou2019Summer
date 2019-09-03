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
class Rank;
class ResultBG;

/**************************************
構造体定義
***************************************/
class ResultSceneUIManager
{
public:
	ResultSceneUIManager();
	~ResultSceneUIManager();

	ResultBG *resultBG;
	Rank * rank;
	void Init(void);
	void Uninit(void);
	void Update(HWND hwnd);
	void Draw(void);
};

#endif
