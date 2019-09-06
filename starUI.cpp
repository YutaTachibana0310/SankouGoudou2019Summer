//=============================================================================
//
// スター画面処理 [starUI.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "starUI.h"
#include "UIdrawer.h"
#include "Framework/Easing.h"
#include "trailUI.h"
#include "InputController.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define NUMBER_ROTATION		(1)
#define SIZE_STAR			(D3DXVECTOR3(100.0f,100.0f,0.0f))
#define VOLUME_ZOOM			(30.0f)
#define DURATION_ROTATION	(60.0f)
#define SPEED_CIRCLE_ROTATE (0.04f)

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
StarButton::StarButton()
{
	// 座標設定
	const float Radius = 420.0f;								//正五角形の半径
	const float BaseAngle = D3DXToRadian(360.0f) / STAR_MAX;	//正五角形の内角
	const float CenterX = (float)SCREEN_CENTER_X;
	const float CenterY = (float)SCREEN_CENTER_Y + 40.0f;

	for (int i = 0; i < STAR_MAX; i++)
	{
		//スター
		star[i] = new RotateObject();
		star[i]->LoadTexture("data/TEXTURE/UI/StarButton/star.png");
		star[i]->CreateObjectCircle();
		star[i]->MakeVertex();
		star[i]->size = SIZE_STAR;
		star[i]->colliderSize = COLLIDERSIZE_STAR;
		star[i]->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		star[i]->SetColorObject(SET_COLOR_NOT_COLORED);
		star[i]->position.x = sinf(i * BaseAngle) * -Radius + CenterX;
		star[i]->position.y = cosf(i * BaseAngle) * -Radius + CenterY;

		//外側のサークル
		outerCircle[i] = new RotateObject();
		outerCircle[i]->LoadTexture("data/TEXTURE/UI/StarButton/outerCircle.png");
		outerCircle[i]->CreateObjectCircle();
		outerCircle[i]->MakeVertex();
		outerCircle[i]->size = SIZE_STAR;
		outerCircle[i]->colliderSize = COLLIDERSIZE_STAR;
		outerCircle[i]->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		outerCircle[i]->SetColorObject(SET_COLOR_NOT_COLORED);
		outerCircle[i]->position.x = sinf(i * BaseAngle) * -Radius + CenterX;
		outerCircle[i]->position.y = cosf(i * BaseAngle) * -Radius + CenterY;

		//内側のサークル
		innerCircle[i] = new RotateObject();
		innerCircle[i]->LoadTexture("data/TEXTURE/UI/StarButton/innerCircle.png");
		innerCircle[i]->CreateObjectCircle();
		innerCircle[i]->MakeVertex();
		innerCircle[i]->size = SIZE_STAR;
		innerCircle[i]->colliderSize = COLLIDERSIZE_STAR;
		innerCircle[i]->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		innerCircle[i]->SetColorObject(SET_COLOR_NOT_COLORED);
		innerCircle[i]->position.x = sinf(i * BaseAngle) * -Radius + CenterX;
		innerCircle[i]->position.y = cosf(i * BaseAngle) * -Radius + CenterY;
	}
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
StarButton::~StarButton()
{
	for (int i = 0; i < STAR_MAX;i++)
	{
		delete star[i];
		star[i] = NULL;

		delete outerCircle[i];
		outerCircle[i] = NULL;

		delete innerCircle[i];
		innerCircle[i] = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void StarButton::Update(HWND hWnd)
{
	for (int i = 0; i < STAR_MAX; i++)
	{
		int InputID = GetMoveInput();
		
		if (InputID == i) {
			ToggleRotateStar(i, true);
		}

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

				outerCircle[i]->size.x = SIZE_STAR.x + VOLUME_ZOOM;
				outerCircle[i]->size.y = SIZE_STAR.y + VOLUME_ZOOM;

				innerCircle[i]->size.x = SIZE_STAR.x + VOLUME_ZOOM;
				innerCircle[i]->size.y = SIZE_STAR.y + VOLUME_ZOOM;
			}
			else
			{	// 元に戻す
				star[i]->size.x = SIZE_STAR.x;
				star[i]->size.y = SIZE_STAR.y;

				outerCircle[i]->size.x = SIZE_STAR.x;
				outerCircle[i]->size.y = SIZE_STAR.y;

				innerCircle[i]->size.x = SIZE_STAR.x;
				innerCircle[i]->size.y = SIZE_STAR.y;
			}

		star[i]->CreateObjectCircle();
		outerCircle[i]->CreateObjectCircle();
		innerCircle[i]->CreateObjectCircle();

		RotateStar(i);
		RotateCircle();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void StarButton::Draw(void)
{
	for (int i = 0; i < STAR_MAX; i++)
	{
		star[i]->Draw();
		star[i]->SetVertex();

		outerCircle[i]->Draw();
		outerCircle[i]->SetVertex();

		innerCircle[i]->Draw();
		innerCircle[i]->SetVertex();
	}
}

//=============================================================================
// スター回転処理
//=============================================================================
void StarButton::RotateStar(int num)
{
	star[num]->countFrame++;
	float t = (float)star[num]->countFrame / DURATION_ROTATION;
	star[num]->rotation = Easing::EaseValue(t, star[num]->easingStartRotation, star[num]->easingGoalRotation, EaseType::OutExpo);
}

//=============================================================================
// スター回転処理
//=============================================================================
void StarButton::RotateCircle(void)
{
	for (int i = 0; i < STAR_MAX; i++)
	{
		outerCircle[i]->rotation.z += SPEED_CIRCLE_ROTATE;
		innerCircle[i]->rotation.z -= SPEED_CIRCLE_ROTATE;
	}
}

//=============================================================================
// 回転処理トグル
//=============================================================================
void StarButton::ToggleRotateStar(int num, bool isRotated)
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
void StarButton::GetStarButtonPosition(std::vector<D3DXVECTOR3>& out)
{
	out.resize(STAR_MAX);

	for (int i = 0; i < STAR_MAX; i++)
	{
		out[i] = star[i]->position;
	}

	return;
}
