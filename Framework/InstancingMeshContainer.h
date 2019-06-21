//=====================================
//
//インスタンシングメッシュコンテナヘッダ[InstancingMeshContainer.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _INSTANCINGMESHCONTAINER_H_
#define _INSTANCINGMESHCONTAINER_H_

#include "../main.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class InstancingMeshContainer
{
public:
	InstancingMeshContainer();
	~InstancingMeshContainer();

	void Load(const char* filePath);
	void Release();
	void Draw();
	void DrawDefault();
	void SetStreamSource(LPDIRECT3DVERTEXBUFFER9 tranformBuffer, UINT numInstance);
	void SetLightAmplifier(float val);

private:
	LPDIRECT3DVERTEXBUFFER9 vtxBuff;
	LPDIRECT3DINDEXBUFFER9 indexuff;
	DWORD fvf;
	LPDIRECT3DVERTEXDECLARATION9 declare;
	D3DXATTRIBUTERANGE *attributeTable;
	DWORD numMaterial;

	LPDIRECT3DTEXTURE9 *textures;
	D3DMATERIAL9 *materials;

	LPD3DXEFFECT effect;
};

#endif