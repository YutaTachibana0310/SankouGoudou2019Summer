//=====================================
//
//ポリゴン2Dヘッダ[Polygon2D.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _POLYGON2D_H_
#define _POLYGON2D_H_

#include "../main.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class Polygon2D
{
public:
	Polygon2D();
	Polygon2D(float sizeX, float sizeY);
	Polygon2D(float sizeX, float sizeY, float texU, float texV);
	virtual ~Polygon2D();

	virtual void Draw();

	virtual void SetSize(float x, float y);
	virtual void SetColor(D3DXCOLOR color);
	virtual void SetUV(float left, float top, float width, float height);

	virtual void LoadTexture(const char* path);

	virtual void InitDiffuse();
	virtual void InitRHW();

	Transform transform;

protected:

	VERTEX_2D vtxWk[NUM_VERTEX];
	LPDIRECT3DTEXTURE9 texture;

	D3DXVECTOR3 vtxPos[NUM_VERTEX];

	LPDIRECT3DDEVICE9 pDevice;

	virtual void SetVertex();
};

#endif