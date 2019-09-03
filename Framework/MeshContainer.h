//=====================================
//
//メッシュコンテナヘッダ[MeshContainer.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _MESHCONTAINER_H_
#define _MESHCONTAINER_H_

#include "../main.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class MeshContainer
{
public:
	MeshContainer();					//コンストラクタ
	~MeshContainer();					//デストラクタ

	HRESULT Load(const char* filePath);	//Xファイルの読み込み
	void Release();						//モデルデータを解放
	void Draw();						//モデルを描画

	void GetMaterial(unsigned id, D3DMATERIAL9 *pOut);		//マテリアル取得
	void GetTexture(unsigned id, LPDIRECT3DTEXTURE9 *pOut);	//テクスチャ取得
	DWORD GetMaterialNum();								//マテリアル数取得

	void SetMaterialColor(const D3DXCOLOR& color);
	void SetMaterialAlpha(float alpha);

private:								
	LPD3DXMESH mesh;					//メッシュデータ
	D3DMATERIAL9* materials;			//マテリアル情報
	LPDIRECT3DTEXTURE9 *textures;		//テクスチャ
	DWORD materialNum;					//マテリアル数
};

#endif