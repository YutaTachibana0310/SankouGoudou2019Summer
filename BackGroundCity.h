//=====================================
//
//バックグラウンドシティヘッダ[BackGroundCity.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BACKGROUNDCITY_H_
#define _BACKGROUNDCITY_H_

#include "main.h"

/**************************************
前方宣言
***************************************/
class MeshContainer;

/**************************************
クラス定義
***************************************/
class BackGroundCity
{
public:
	BackGroundCity(const char* meshTag);
	~BackGroundCity();

	void Init();
	void Uninit();
	void Update(float speed);
	void Draw(D3DXMATRIX mtxParent);

	Transform transform;

	static float depthMaxZ;

private:
	MeshContainer* mesh;

};

#endif