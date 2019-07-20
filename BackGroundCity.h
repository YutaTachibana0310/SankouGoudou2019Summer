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
	void Update();
	void Draw();

	Transform transform;

private:
	MeshContainer* mesh;
	int cntFrame;
	float alpha;

	static float moveSpeed;
	static int frameFadein;
};
/**************************************
プロトタイプ宣言
***************************************/
void InitBackGroundCity(int num);
void UninitBackGroundCity(int num);
void UpdateBackGroundCity(void);
void DrawBackGroundCity(void);

#endif