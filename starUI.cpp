//=============================================================================
//
// スター画面処理 [star.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "starUI.h"
#include "UIdrawer.h"
#include "Framework/EasingVector.h"
#include "trailUI.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define NUMBER_ROTATION		(1)
#define SIZE_STAR			(D3DXVECTOR3(100.0f,100.0f,0.0f))
#define VOLUME_ZOOM			(30.0f)
#define DURATION_ROTATION	(60.0f)

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
Star::Star()
{
	for (int i = 0; i < STAR_MAX; i++)
	{
		star[i] = new RotateObject();

		star[i]->LoadTexture("data/TEXTURE/UI/star.png");
		star[i]->CreateObjectCircle();
		star[i]->MakeVertex();

		star[i]->size = SIZE_STAR;
		star[i]->colliderSize = COLLIDERSIZE_STAR;
		star[i]->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	// 座標設定
	const float Radius = 420.0f;								//正五角形の半径
	const float BaseAngle = D3DXToRadian(360.0f) / STAR_MAX;	//正五角形の内角
	const float CenterX = (float)SCREEN_CENTER_X;
	const float CenterY = (float)SCREEN_CENTER_Y + 40.0f;
	for (int i = 0; i < STAR_MAX; i++)
	{
		star[i]->position.x = sinf(i * BaseAngle) * -Radius + CenterX;
		star[i]->position.y = cosf(i * BaseAngle) * -Radius + CenterY;
	}

	//　色設定
	star[TOP]->SetColorObject(SET_COLOR_NOT_COLORED);
	star[MIDDLE_LEFT]->SetColorObject(SET_COLOR_NOT_COLORED);
	star[LOWER_LEFT]->SetColorObject(SET_COLOR_NOT_COLORED);
	star[LOWER_RIGHT]->SetColorObject(SET_COLOR_NOT_COLORED);
	star[MIDDLE_RIGHT]->SetColorObject(SET_COLOR_NOT_COLORED);
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
Star::~Star()
{
	for (int i = 0; i < STAR_MAX;i++)
	{
		delete star[i];
		star[i] = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void Star::Update(HWND hWnd)
{
	for (int i = 0; i < STAR_MAX; i++)
	{
			if (star[i]->IsMouseOvered(hWnd,star[i]->position,
				star[i]->colliderSize))
			{
				if (IsMouseLeftTriggered())
				{
					ToggleRotateStar(i,true);
				}
				// 選択されているなら拡大表示
				star[i]->size.x = SIZE_STAR.x + VOLUME_ZOOM;
				star[i]->size.y = SIZE_STAR.y + VOLUME_ZOOM;
			}
			else
			{	// 元に戻す
				star[i]->size.x = SIZE_STAR.x;
				star[i]->size.y = SIZE_STAR.y;
			}

		star[i]->CreateObjectCircle();
		RotateStar(i);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void Star::Draw(void)
{
	for (int i = 0; i < STAR_MAX; i++)
	{
		star[i]->Draw();
		star[i]->SetVertex();
	}
}

//=============================================================================
// 回転処理
//=============================================================================
void Star::RotateStar(int num)
{
	star[num]->countFrame++;
	float t = (float)star[num]->countFrame / DURATION_ROTATION;
	star[num]->rotation = 
		EaseOutExponentialVector(t, star[num]->easingStartRotation, star[num]->easingGoalRotation);
}

//=============================================================================
// 回転処理トグル
//=============================================================================
void Star::ToggleRotateStar(int num, bool isRotated)
{
	star[num]->rotation.z = 0.0f;
	star[num]->countFrame = 0;
	star[num]->easingStartRotation = star[num]->rotation;
	star[num]->isRotated = isRotated;

	if (star[num]->isRotated == true && star[num]->rotation.z < D3DXToRadian(360.0f) * NUMBER_ROTATION)
	{
		star[num]->easingGoalRotation = 
			star[num]->easingStartRotation + D3DXVECTOR3(0.0f, 0.0f, D3DXToRadian(360.0f) * NUMBER_ROTATION);
	}
	else if (star[num]->rotation.z >= D3DXToRadian(360.0f) * NUMBER_ROTATION)
	{
		star[num]->easingGoalRotation = star[num]->easingStartRotation;
		star[num]->easingGoalRotation.z = D3DXToRadian(360.0f) * NUMBER_ROTATION;
		star[num]->rotation.z = 0.0f;
		star[num]->easingStartRotation = star[num]->rotation;
		star[num]->isRotated = false;
	}
}

//=============================================================================
// 星座標取得用
//=============================================================================
D3DXVECTOR3* Star::GetStarPosition(void)
{
	D3DXVECTOR3 *pos = {};

	for (int i = 0; i < STAR_MAX; i++)
	{
		pos[i] = star[i]->position;
	}

	return pos;
}
