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
	~SkyBox();

	void Update();
	void Draw();

	void LoadTexture(const char* path);

	Transform transform;

private:
	LPDIRECT3DTEXTURE9 texture;
	LPDIRECT3DVERTEXBUFFER9 vtxBuff;
};

#endif