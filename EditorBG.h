//=====================================
//
//エディタBGヘッダ[EditorBG.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _EDITORBG_H_
#define _EDITORBG_H_

#include "main.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class EditorBG
{
public:
	EditorBG();
	~EditorBG();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	LPDIRECT3DTEXTURE9 texture;
	VERTEX_2D vtxWk[NUM_VERTEX];
};

#endif