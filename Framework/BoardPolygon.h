//=====================================
//
//�|���S���w�b�_[BoardPolygon.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _BOARDPOLYGON_H_
#define _BOARDPOLYGON_H_

#include "../main.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class BoardPolygon
{
public:
	BoardPolygon();
	~BoardPolygon();

	void Draw();

	void LoadTexture(const char* path);

	void SetSize(D3DXVECTOR2 size);
	void SetTexDiv(D3DXVECTOR2 div);

	void SetTextureIndex(int index);

private:
	LPDIRECT3DDEVICE9 pDevice;

	LPDIRECT3DVERTEXBUFFER9 vtxBuff;
	LPDIRECT3DTEXTURE9 texture;

	D3DXVECTOR2 texDiv;
	D3DXVECTOR2 texSize;
};

#endif