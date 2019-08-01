//=============================================================================
//
// カーソル画面処理 [cursor.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _CURSOR_H_
#define _CURSOR_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	ADRESS_TEXTURE_CURSOR	("data/TEXTURE/UI/cursor.png")	// 読み込むテクスチャファイル名
#define COLLIDERSIZE_CURSOR (D3DXVECTOR3(5.0f,5.0f,0.0f))

#include "GameSceneUIManager.h"

#include "UIdrawer.h"

class Object;

/**************************************
前方宣言
***************************************/
class GameSceneUI;

//*****************************************************************************
// 構造体定義
//*****************************************************************************
class Cursor :public GameSceneUI
{
public:
	Object*object;
	void Init(void);
	void Uninit(void);
	void Update(HWND hWnd);
	void Draw(void);
	bool IsCursorOvered(D3DXVECTOR3 pos, D3DXVECTOR3 size);

private:
	bool IsStarHitted(int num);
};

#endif
