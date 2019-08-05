//=============================================================================
//
// カーソル画面処理 [cursor.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "cursorUI.h"
#include "UIdrawer.h"
#include "starUI.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SIZE_CURSOR		(D3DXVECTOR3(40.0f,40.0f,0.0f))
#define SPEED_ROTATION	(0.10f)

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//=============================================================================
// 初期化処理
//=============================================================================
void Cursor::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	LoadTexture(pDevice, ADRESS_TEXTURE_CURSOR);
	InitialTexture();
	MakeVertexRotateObject();

	position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	size		= SIZE_CURSOR;
	rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	colliderSize = COLLIDERSIZE_CURSOR / 2;

	SetColorObject(SET_COLOR_YELLOW);

	// 回転オブジェクト用のサークルを作成
	CreateObjectCircle();
}

//=============================================================================
// 終了処理
//=============================================================================
void Cursor::Uninit(void)
{
	ReleaseTexture();
}

//=============================================================================
// 更新処理
//=============================================================================
void Cursor::Update(HWND hWnd)
{
	position = GetMousePosition(hWnd);

	for (int i = 0; i < STAR_MAX; i++)
	{
		if (IsStarHitted(i))
		{
			// 選択されているなら
			SetColorObject(SET_COLOR_RED);
		}
		else
		{	// 元に戻す
			SetColorObject(SET_COLOR_YELLOW);
		}
	}

	rotation.z -= SPEED_ROTATION;
}

//=============================================================================
// 描画処理
//=============================================================================
void Cursor::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	DrawObject(pDevice);
	SetVertexRotateObject();
}

//=============================================================================
// 選択されているかの判定処理 (当たったら選択状態)
//=============================================================================
bool Cursor::IsStarHitted(int num)
{
	D3DXVECTOR3 starPosition[STAR_MAX];
	GetStarPosition(starPosition);

	// どのスターとも当たってなかったらfalse,それ以外はtrue
	if (IsCursorOvered(starPosition[0], COLLIDERSIZE_STAR))
		return true;

	if (IsCursorOvered(starPosition[1], COLLIDERSIZE_STAR))
		return true;

	if (IsCursorOvered(starPosition[2], COLLIDERSIZE_STAR))
		return true;

	if (IsCursorOvered(starPosition[3], COLLIDERSIZE_STAR))
		return true;

	if (IsCursorOvered(starPosition[4], COLLIDERSIZE_STAR))
		return true;

	return false;
}

//=============================================================================
// カーソルが重なったかの判定処理
//=============================================================================
bool Cursor::IsCursorOvered(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	size /= 2.0f;	// 半サイズにする

	if (position.x + colliderSize.x > pos.x - size.x 
		&& pos.x + size.x > position.x - colliderSize.x 
		&&
		position.y + colliderSize.y > pos.y - size.y 
		&& pos.y + size.y > position.y - colliderSize.y)
	{
		return true;
	}

	return false;
}
