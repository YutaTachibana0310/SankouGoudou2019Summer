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
#include "cursorUI.h"
#include "trailUI.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define NUMBER_ROTATION		(1)
#define SIZE_STAR			(D3DXVECTOR3(100.0f,100.0f,0.0f))
#define VOLUME_ZOOM			(30.0f)
#define DURATION_ROTATION	(60.0f)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
Object	star[STAR_MAX];

//=============================================================================
// 初期化処理
//=============================================================================
void Star::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < STAR_MAX; i++)
	{
		object->LoadTexture(pDevice, ADRESS_TEXTURE_STAR, &star[i]);
		object->CreateObjectCircle(&star[i], star[i].size.x, star[i].size.y);
		object->InitialTexture(&star[i]);
		object->MakeVertexRotateObject(&star[i]);

		star[i].size = SIZE_STAR;
		star[i].colliderSize = COLLIDERSIZE_STAR;
		star[i].rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	// 座標設定
	const float Radius = 420.0f;								//正五角形の半径
	const float BaseAngle = D3DXToRadian(360.0f) / STAR_MAX;	//正五角形の内角
	const float CenterX = (float)SCREEN_CENTER_X;
	const float CenterY = (float)SCREEN_CENTER_Y + 40.0f;
	for (int i = 0; i < STAR_MAX; i++)
	{
		star[i].position.x = sinf(i * BaseAngle) * -Radius + CenterX;
		star[i].position.y = cosf(i * BaseAngle) * -Radius + CenterY;
	}

	//　色設定
	object->SetColorObject(&star[TOP],			SET_COLOR_NOT_COLORED);
	object->SetColorObject(&star[MIDDLE_LEFT],	SET_COLOR_NOT_COLORED);
	object->SetColorObject(&star[LOWER_LEFT],	SET_COLOR_NOT_COLORED);
	object->SetColorObject(&star[LOWER_RIGHT],	SET_COLOR_NOT_COLORED);
	object->SetColorObject(&star[MIDDLE_RIGHT], SET_COLOR_NOT_COLORED);
}

//=============================================================================
// 終了処理
//=============================================================================
void Star::Uninit(void)
{
	for (int i = 0; i < STAR_MAX; i++)
	{
		object->ReleaseTexture(&star[i]);
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void Star::Update(void)
{
	for (int i = 0; i < STAR_MAX; i++)
	{
			if (IsStarSelected(i))
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

		object->CreateObjectCircle(&star[i], star[i].size.x, star[i].size.y);
		RotateStar(i);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void Star::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < STAR_MAX; i++)
	{
		object->DrawObject(pDevice, &star[i]);
		object->SetVertexRotateObject(&star[i]);
	}
}

//=============================================================================
// 回転処理
//=============================================================================
void Star::RotateStar(int num)
{
	star[num].countFrame++;
	float t = (float)star[num].countFrame / DURATION_ROTATION;
	star[num].rotation = 
		EaseOutExponentialVector(t, star[num].easingStartRotation, star[num].easingGoalRotation);
}

//=============================================================================
// 回転処理トグル
//=============================================================================
void Star::ToggleRotateStar(int num, bool isRotated)
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
bool Star::IsStarSelected(int num)
{
	return cursor->IsCursorOvered(star[num].position,star[num].colliderSize);
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