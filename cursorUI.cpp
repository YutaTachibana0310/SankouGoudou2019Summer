//=============================================================================
//
// カーソル画面処理 [outerCircle.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "UIdrawer.h"
#include "GameSceneUIManager.h"
#include "cursorUI.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SIZE_CURSOR		(D3DXVECTOR3(45.0f,45.0f,0.0f))
#define SPEED_ROTATION	(0.10f)
#define COLLIDERSIZE_CURSOR (D3DXVECTOR3(5.0f,5.0f,0.0f))

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
Cursor::Cursor()
{
	//外側のサークル
	outerCircle = new RotateObject();
	outerCircle->LoadTexture("data/TEXTURE/UI/Cursor/outerCircle.png");
	outerCircle->MakeVertex();
	outerCircle->position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	outerCircle->size = SIZE_CURSOR;
	outerCircle->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	outerCircle->colliderSize = COLLIDERSIZE_CURSOR / 2;
	outerCircle->SetColorObject(SET_COLOR_NOT_COLORED);
	outerCircle->CreateObjectCircle();

	//内側のサークル
	innerCircle = new RotateObject();
	innerCircle->LoadTexture("data/TEXTURE/UI/Cursor/innerCircle.png");
	innerCircle->MakeVertex();
	innerCircle->position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	innerCircle->size = SIZE_CURSOR;
	innerCircle->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	innerCircle->colliderSize = COLLIDERSIZE_CURSOR / 2;
	innerCircle->SetColorObject(SET_COLOR_NOT_COLORED);
	innerCircle->CreateObjectCircle();
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
Cursor::~Cursor()
{
	delete outerCircle;
	outerCircle = NULL;

	delete innerCircle;
	innerCircle = NULL;
}

//=============================================================================
// 更新処理
//=============================================================================
void Cursor::Update(HWND hWnd)
{
	outerCircle->position = GetMousePosition(hWnd);
	outerCircle->rotation.z -= SPEED_ROTATION;

	innerCircle->position = GetMousePosition(hWnd);
	innerCircle->rotation.z += SPEED_ROTATION;
}

//=============================================================================
// 描画処理
//=============================================================================
void Cursor::Draw(void)
{
	outerCircle->Draw();
	outerCircle->SetVertex();

	innerCircle->Draw();
	innerCircle->SetVertex();
}

//=============================================================================
// カーソルが重なったかの判定処理(外側のサークルとの当たり判定)
//=============================================================================
bool Cursor::IsCursorOvered(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	size /= 2.0f;	// 半サイズにする

	if (outerCircle->position.x +outerCircle->colliderSize.x > pos.x - size.x 
		&& pos.x + size.x > outerCircle->position.x -outerCircle->colliderSize.x 
		&& outerCircle->position.y +outerCircle->colliderSize.y > pos.y - size.y 
		&& pos.y + size.y > outerCircle->position.y -outerCircle->colliderSize.y)
	{
		return true;
	}

	return false;
}

//*****************************************************************************
// ボタン選択状態に色更新
//*****************************************************************************
void Cursor::PaintCursorRed()
{
	outerCircle->SetColorObject(SET_COLOR_RED);
	innerCircle->SetColorObject(SET_COLOR_RED);
}

//*****************************************************************************
// 非ボタン選択状態に色更新
//*****************************************************************************
void Cursor::PaintCursorYellow()
{
	outerCircle->SetColorObject(SET_COLOR_NOT_COLORED);
	innerCircle->SetColorObject(SET_COLOR_NOT_COLORED);
}
