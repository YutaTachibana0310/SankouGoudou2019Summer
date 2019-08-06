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

typedef struct
{
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
	int					countFrame;
	float               baseAngle;
	float				radius;
	bool				isRotated;
	bool				use;

}OBJECT;

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

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

void LoadTexture			(LPDIRECT3DDEVICE9 device, const char *adress, OBJECT *object);
void CreateObjectCircle		(OBJECT *object, float sizeX, float sizeY);
void ReleaseTexture			(OBJECT *object);
void InitialTexture			(OBJECT *object);
void DrawObject				(LPDIRECT3DDEVICE9 pDevice, OBJECT object);
void MakeVertexObject		(OBJECT *object);
void MakeVertexRotateObject	(OBJECT *object);
void MakeVertexGuageBar		(OBJECT *object, float percentage, float flameWidth);
void SetVertexObject		(OBJECT *object);
void SetVertexRotateObject	(OBJECT *object);
void SetVertexGuageBar		(OBJECT *object, float percentage, float flameWidth, int guageType);
void SetVertexTelopBG		(OBJECT *object, float percentage);
void SetVertexCounter		(OBJECT *object, int placeCount, float placeInterval);
void SetTextureObject		(OBJECT *object, int divX, int divY, int pattern);
void SetTextureCounter		(OBJECT *object, int number, float placeInterval);
void SetAlphaObject			(OBJECT *object, float alpha);
void SetColorObject			(OBJECT *object, D3DXCOLOR color);
float GetCountObject		(OBJECT *object, float duration);

#endif

