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
#include "Framework/EasingVector.h"
#include "cursor.h"
#include "trail.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define NUMBER_ROTATION		(1)
#define SIZE_STAR			(D3DXVECTOR3(100.0f,100.0f,0.0f))
#define VOLUME_ZOOM			(30.0f)
#define SPEED_ROTATION		(60.0f)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void RotateStar(int num);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
OBJECT	star[STAR_MAX];

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

		star[i].size = SIZE_STAR;
		star[i].colliderSize = COLLIDERSIZE_STAR;
		star[i].rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	// 座標設定
	star[TOP].position			= POSITION_STAR_TOP;
	star[MIDDLE_LEFT].position	= POSITION_STAR_MIDDLE_LEFT;
	star[LOWER_LEFT].position	= POSITION_STAR_LOWER_LEFT;
	star[LOWER_RIGHT].position	= POSITION_STAR_LOWER_RIGHT;
	star[MIDDLE_RIGHT].position = POSITION_STAR_MIDDLE_RIGHT;

	//　色設定
	SetColorObject(&star[TOP],			SET_COLOR_NOT_COLORED);
	SetColorObject(&star[MIDDLE_LEFT],	SET_COLOR_NOT_COLORED);
	SetColorObject(&star[LOWER_LEFT],	SET_COLOR_NOT_COLORED);
	SetColorObject(&star[LOWER_RIGHT],	SET_COLOR_NOT_COLORED);
	SetColorObject(&star[MIDDLE_RIGHT], SET_COLOR_NOT_COLORED);

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
			if (IsStarSelected(i,hWnd))
			{
				if (IsMouseLeftTriggered())
				{
					ToggleRotateStar(i,true);
				}
				// 選択されているなら拡大表示
				star[i].size.x = SIZE_STAR.x + VOLUME_ZOOM;
				star[i].size.y = SIZE_STAR.y + VOLUME_ZOOM;
			}
			else
			{	// 元に戻す
				star[i].size.x = SIZE_STAR.x;
				star[i].size.y = SIZE_STAR.y;
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
		SetVertexRotateObject(&star[i]);
	}
}

//=============================================================================
// 回転処理
//=============================================================================
void RotateStar(int num)
{
	star[num].countFrame++;
	float t = (float)star[num].countFrame / SPEED_ROTATION;
	star[num].rotation = 
		EaseOutExponentialVector(t, star[num].easingStartRotation, star[num].easingGoalRotation);
}

//=============================================================================
// 回転処理トグル
//=============================================================================
void ToggleRotateStar(int num, bool isRotated)
{
	star[num].rotation.z = 0.0f;
	star[num].countFrame = 0;
	star[num].easingStartRotation = star[num].rotation;
	star[num].isRotated = isRotated;

	if (star[num].isRotated == true && star[num].rotation.z < D3DXToRadian(360.0f) * NUMBER_ROTATION)
	{
		star[num].easingGoalRotation = 
			star[num].easingStartRotation + D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(360.0f) * NUMBER_ROTATION);
	}
	else if (star[num].rotation.z >= D3DXToRadian(360.0f) * NUMBER_ROTATION)
	{
		star[num].easingGoalRotation = star[num].easingStartRotation;
		star[num].easingGoalRotation.z = D3DXToRadian(360.0f) * NUMBER_ROTATION;
		star[num].rotation.z = 0.0f;
		star[num].easingStartRotation = star[num].rotation;
		star[num].isRotated = false;
	}
}

//=============================================================================
// 選択されているかの判定処理 (当たったら選択状態)
//=============================================================================
bool IsStarSelected(int num, HWND hWnd)
{
	return IsCursorOverd(hWnd,star[num].position,star[num].colliderSize);
}

//=============================================================================
// 星座標取得用（渡邉追記）
//=============================================================================
void GetStarPosition(D3DXVECTOR3 *pos) {
	for (int i = 0; i < STAR_MAX; i++)
	{
		pos[i] = star[i].position;
	}
}