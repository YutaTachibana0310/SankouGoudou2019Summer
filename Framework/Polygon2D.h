//=====================================
//
//�|���S��2D�w�b�_[Polygon2D.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _POLYGON2D_H_
#define _POLYGON2D_H_

#include "../main.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class Polygon2D
{
public:
	Polygon2D();
	~Polygon2D();

	void Draw();

	void SetSize(float x, float y);
	void SetColor(D3DXCOLOR color);
	void SetUV(float left, float top, float width, float height);

	void LoadTexture(const char* path);

	Transform transform;

private:
	VERTEX_2D vtxWk[NUM_VERTEX];
	LPDIRECT3DTEXTURE9 texture;

	D3DXVECTOR3 vtxPos[NUM_VERTEX];

	LPDIRECT3DDEVICE9 pDevice;

	void SetVertex();
};

#endif