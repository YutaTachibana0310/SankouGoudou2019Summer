//=============================================================================
//
// スター画面処理 [star.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "star.h"
#include "UIdrawer.h"
#include "collider.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	STAR_MAX	(5)
#define NUMBER_ROTATION (1)
#define SIZE_X_STAR (100.0f)
#define SIZE_Y_STAR (100.0f)
#define COLLIDERSIZE_X_STAR (120.0f)
#define COLLIDERSIZE_Y_STAR (120.0f)
#define VOLUME_ZOOM (30.0f)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void RotateStar(int num);
bool IsSelected(HWND hWnd, int num);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
OBJECT	star[STAR_MAX];
bool rotateUse = false;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitStar(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < STAR_MAX; i++)
	{
		LoadTexture(pDevice, ADRESS_TEXTURE_STAR, &star[i]);
		CreateObjectCircle(&star[i], star[i].size.x, star[i].size.y);
		InitialTexture(&star[i]);
		MakeVertexRotateObject(&star[i]);

		// 座標設定
		star[TOP].position = POSITION_STAR_TOP;
		star[MIDDLE_LEFT].position = POSITION_STAR_MIDDLE_LEFT;
		star[LOWER_LEFT].position = POSITION_STAR_LOWER_LEFT;
		star[LOWER_RIGHT].position = POSITION_STAR_LOWER_RIGHT;
		star[MIDDLE_RIGHT].position = POSITION_STAR_MIDDLE_RIGHT;

		star[i].size = D3DXVECTOR3(SIZE_X_STAR, SIZE_Y_STAR, 0.0f);
		star[i].colliderSize = D3DXVECTOR3(COLLIDERSIZE_X_STAR, COLLIDERSIZE_X_STAR, 0.0f);
		star[i].rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//　色設定
		SetColorObject(&star[TOP], SET_COLOR_YELLOW);
		SetColorObject(&star[MIDDLE_LEFT], SET_COLOR_PINK);
		SetColorObject(&star[LOWER_LEFT], SET_COLOR_RIGHTBLUE);
		SetColorObject(&star[LOWER_RIGHT], SET_COLOR_RED);
		SetColorObject(&star[MIDDLE_RIGHT], SET_COLOR_GREEN);
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitStar(void)
{
	for (int i = 0; i < STAR_MAX; i++)
	{
		ReleaseTexture(&star[i]);
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateStar(HWND hWnd)
{
	for (int i = 0; i < STAR_MAX; i++)
	{
			if (IsSelected(hWnd,i))
			{
				if (IsMouseLeftTriggered())
				{
					star[i].rotateUse = true;
				}
				star[i].size.x = SIZE_X_STAR + VOLUME_ZOOM;
				star[i].size.y = SIZE_Y_STAR + VOLUME_ZOOM;
			}
			else
			{
				star[i].size.x = SIZE_X_STAR;
				star[i].size.y = SIZE_Y_STAR;
			}

		CreateObjectCircle(&star[i], star[i].size.x, star[i].size.y);
		RotateStar(i);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawStar(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < STAR_MAX; i++)
	{
		DrawObject(pDevice, star[i]);

		// 頂点座標の設定
		SetVertexRotateObject(&star[i]);
	}
}

//=============================================================================
// 回転処理
//=============================================================================
void RotateStar(int num)
{
	if (star[num].rotateUse == true && star[num].rotation.z < 360 * D3DX_PI / 180 * NUMBER_ROTATION)
	{
		star[num].rotation.z += 0.1*D3DX_PI;
	}
	if(star[num].rotation.z >= 360 * D3DX_PI / 180 * NUMBER_ROTATION)
	{
		star[num].rotation.z = 0.0f;
		star[num].rotateUse = false;
	}
}

//=============================================================================
// 選択されているかの判定処理 (当たったら選択状態)
//=============================================================================
bool IsSelected(HWND hWnd, int num)
{
	return IsHittedBB(GetMousePosition(hWnd), star[num].position, D3DXVECTOR2(star[num].colliderSize.x, star[num].colliderSize.y), D3DXVECTOR2(COLLIDERSIZE_X_CURSOR, COLLIDERSIZE_Y_CURSOR));
}
