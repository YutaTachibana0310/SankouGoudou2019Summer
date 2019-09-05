//=============================================================================
//
// UI描画用処理 [UIdrawer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _UIDRAWER_H_
#define _UIDRAWER_H_

#include "main.h"

/**************************************
前方宣言
***************************************/
//class Viewer3D {};


//*****************************************************************************
// マクロ定義
//*****************************************************************************
// 色定義
#define SET_COLOR_NOT_COLORED	(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))
#define SET_COLOR_BLACK			(D3DXCOLOR(0.0f,0.0f,0.0f,1.0f))
#define SET_COLOR_RED			(D3DXCOLOR(1.0f,0.0f,0.0f,1.0f))
#define SET_COLOR_GREEN			(D3DXCOLOR(0.0f,1.0f,0.0f,1.0f))
#define SET_COLOR_BLUE			(D3DXCOLOR(0.0f,0.0f,1.0f,1.0f))
#define SET_COLOR_YELLOW		(D3DXCOLOR(1.0f,1.0f,0.0f,1.0f))
#define SET_COLOR_PINK			(D3DXCOLOR(1.0f,0.0f,1.0f,1.0f))
#define SET_COLOR_RIGHTBLUE		(D3DXCOLOR(0.0f,1.0f,1.0f,1.0f))
#define SET_COLOR_ORANGE		(D3DXCOLOR(1.0f,0.4f,0.0f,1.0f))

//*****************************************************************************
// 構造体定義
//*****************************************************************************
class Object
{
public:
	LPDIRECT3DTEXTURE9	texture;
	VERTEX_2D			vertexWk[NUM_VERTEX];
	D3DXVECTOR3			position;
	D3DXVECTOR3			rotation;
	D3DXVECTOR3			size;
	D3DXVECTOR3			colliderSize;

	int					countFrame;

	void LoadTexture(const char *path);
	void ReleaseTexture();
	void Draw();
	void SetAlphaObject(float alpha);
	void SetColorObject(D3DXCOLOR color);
	float GetCountObject(float duration);
	bool IsMouseOvered(HWND hWnd, D3DXVECTOR3 pos, D3DXVECTOR3 size);

	virtual void MakeVertex();
	virtual void SetVertex();
	virtual void SetTexture(int divX, int divY, int pattern);
};

class RotateObject:public Object
{
public:
	D3DXVECTOR3	easingStartRotation;
	D3DXVECTOR3	easingGoalRotation;

	bool isRotated;
	float baseAngle;
	float radius;

	void CreateObjectCircle();
	void MakeVertex();
	void SetVertex();
};

class GuageObject :public Object
{
public:
	void MakeVertex(float percentage, float flameWidth);
	void SetVertex(float percentage, float flameWidth, int guageType);

	enum GUAGETYPE
	{
		LEFT_GUAGEBAR,
		RIGHT_GUAGEBAR,
		UP_GUAGEBAR,
		DOWN_GUAGEBAR
	};
};

class CounterObject :public Object
{
public:
	void SetVertex(int placeCount, float placeInterval);
	void SetTexture(int number, float placeInterval);
};

class TelopObject :public Object
{
public:
};

#endif

