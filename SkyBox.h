//=====================================
//
//スカイボックスヘッダ[SkyBox.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _SKYBOX_H_
#define _SKYBOX_H_

#include "main.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class SkyBox
{
public:
	SkyBox(D3DXVECTOR3 vtxSize, D3DXVECTOR2 texSize);
	virtual ~SkyBox();

	virtual void Draw();

	virtual void LoadTexture(const char* path);
	virtual void SetUV(float texU, float texV);

protected:
	Transform * transform;
	LPDIRECT3DTEXTURE9 texture;
	LPDIRECT3DVERTEXBUFFER9 vtxBuff;

	void MakeVertexBuffer(float width, float height, float depth);

	enum Const
	{
		FieldNum = 4,		//面の数
	};
};

#endif