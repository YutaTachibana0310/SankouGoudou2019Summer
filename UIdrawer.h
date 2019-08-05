//=============================================================================
//
// UI描画用処理 [UIdrawer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _UIDRAWER_H_
#define _UIDRAWER_H_

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
	D3DXVECTOR3			easingStartRotation;
	D3DXVECTOR3			easingGoalRotation;
	D3DXVECTOR3			easingStartPosition;
	D3DXVECTOR3			easingGoalPosition;
	D3DXVECTOR3			easingStartSize;
	D3DXVECTOR3			easingGoalSize;

	float				easingStart;
	float				easingGoal;
	float               baseAngle;
	float				radius;
	int					countFrame;
	bool				isRotated;

	void LoadTexture(LPDIRECT3DDEVICE9 device, const char *path);
	void CreateObjectCircle();
	void ReleaseTexture();
	void InitialTexture();
	void DrawObject(LPDIRECT3DDEVICE9 pDevice);
	void MakeVertexObject();
	void MakeVertexRotateObject();
	void MakeVertexGuageBar(float percentage, float flameWidth);
	void SetVertexObject();
	void SetVertexRotateObject();
	void SetVertexGuageBar(float percentage, float flameWidth, int guageType);
	void SetVertexTelopBG(float percentage);
	void SetVertexCounter(int placeCount, float placeInterval);
	void SetTextureObject(int divX, int divY, int pattern);
	void SetTextureCounter(int number, float placeInterval);
	void SetAlphaObject(float alpha);
	void SetColorObject(D3DXCOLOR color);
	float GetCountObject(float duration);
};

enum GUAGETYPE
{
	LEFT_GUAGEBAR,
	RIGHT_GUAGEBAR,
	UP_GUAGEBAR,
	DOWN_GUAGEBAR
};

enum TELOP_ANIM_SCENE
{
	WAIT_BG_OPEN,
	IN_TEXT,
	STOP_TEXT,
	OUT_TEXT,
	WAIT_BG_CLOSE
};

#endif

