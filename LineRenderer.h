//=====================================
//
//ラインレンダラーヘッダ[LineRenderer.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _LINERENDERER_H_
#define _LINERENDERER_H_

#include "main.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class LineRenderer
{
public:
	LineRenderer();
	~LineRenderer();

	void Init(D3DXVECTOR3 *right, D3DXVECTOR3 *left, float width);
	void Draw();
	void SetRightPos(D3DXVECTOR3 *pos);
	void SetLeftPos(D3DXVECTOR3 *pos);
	void SetColor(D3DXCOLOR color);

private:
	LPDIRECT3DVERTEXBUFFER9 vtxBuff;
	D3DXVECTOR3 vtxUp;
	float width;
};

#endif