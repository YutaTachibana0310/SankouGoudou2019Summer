//=============================================================================
//
// UI�`��p���� [UIdrawer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _UIDRAWER_H_
#define _UIDRAWER_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// �F��`
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
// �\���̒�`
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

	void LoadTexture(LPDIRECT3DDEVICE9 device, const char *adress, Object *object);
	void CreateObjectCircle(Object *object, float sizeX, float sizeY);
	void ReleaseTexture(Object *object);
	void InitialTexture(Object *object);
	void DrawObject(LPDIRECT3DDEVICE9 pDevice, Object *object);
	void MakeVertexObject(Object *object);
	void MakeVertexRotateObject(Object *object);
	void MakeVertexGuageBar(Object *object, float percentage, float flameWidth);
	void SetVertexObject(Object *object);
	void SetVertexRotateObject(Object *object);
	void SetVertexGuageBar(Object *object, float percentage, float flameWidth, int guageType);
	void SetVertexTelopBG(Object *object, float percentage);
	void SetVertexCounter(Object *object, int placeCount, float placeInterval);
	void SetTextureObject(Object *object, int divX, int divY, int pattern);
	void SetTextureCounter(Object *object, int number, float placeInterval);
	void SetAlphaObject(Object *object, float alpha);
	void SetColorObject(Object *object, D3DXCOLOR color);
	float GetCountObject(Object *object, float duration);
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

