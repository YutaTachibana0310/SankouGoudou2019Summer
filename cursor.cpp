//=============================================================================
//
// カーソル画面処理 [cursor.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "cursor.h"
#include "UIdrawer.h"
#include "star.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SIZE_CURSOR		(D3DXVECTOR3(40.0f,40.0f,0.0f))
#define SPEED_ROTATION	(0.10f)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
OBJECT	cursor;
bool	IsStarHitted(int num, HWND hWnd);

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitCursor(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	LoadTexture(pDevice, ADRESS_TEXTURE_CURSOR, &cursor);
	InitialTexture(&cursor);
	MakeVertexRotateObject(&cursor);

	cursor.position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	cursor.size		= SIZE_CURSOR;
	cursor.rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	SetColorObject(&cursor, SET_COLOR_YELLOW);

	// 回転オブジェクト用のサークルを作成
	CreateObjectCircle(&cursor, cursor.size.x, cursor.size.y);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitCursor(void)
{
	ReleaseTexture(&cursor);
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateCursor(HWND hWnd)
{
	cursor.position = GetMousePosition(hWnd);

	for (int i = 0; i < STAR_MAX; i++)
	{
		if (IsStarHitted(i, hWnd))
		{
			// 選択されているなら
			SetColorObject(&cursor, SET_COLOR_RED);
		}
		else
		{	// 元に戻す
			SetColorObject(&cursor, SET_COLOR_YELLOW);
		}
	}

	cursor.rotation.z -= SPEED_ROTATION;
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawCursor(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	DrawObject(pDevice, cursor);
	SetVertexRotateObject(&cursor);
}

//=============================================================================
// 選択されているかの判定処理 (当たったら選択状態)
//=============================================================================
bool IsStarHitted(int num, HWND hWnd)
{
	D3DXVECTOR3 starPosition[STAR_MAX];
	GetStarPosition(starPosition);

	// どのスターとも当たってなかったらfalse,それ以外はtrue
	if (IsCursorOverd(hWnd, starPosition[0], COLLIDERSIZE_STAR))
		return true;

	if (IsCursorOverd(hWnd, starPosition[1], COLLIDERSIZE_STAR))
		return true;

	if (IsCursorOverd(hWnd, starPosition[2], COLLIDERSIZE_STAR))
		return true;

	if (IsCursorOverd(hWnd, starPosition[3], COLLIDERSIZE_STAR))
		return true;

	if (IsCursorOverd(hWnd, starPosition[4], COLLIDERSIZE_STAR))
		return true;

	return false;
}

//=============================================================================
// カーソルが重なったかの判定処理
//=============================================================================
bool IsCursorOverd(HWND hWnd,D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	size /= 2.0f;	// 半サイズにする

	D3DXVECTOR3 cursorSize = COLLIDERSIZE_CURSOR / 2;

	if (GetMousePosition(hWnd).x + cursorSize.x > pos.x - size.x 
		&& pos.x + size.x > GetMousePosition(hWnd).x - cursorSize.x 
		&&
		GetMousePosition(hWnd).y + cursorSize.y > pos.y - size.y 
		&& pos.y + size.y > GetMousePosition(hWnd).y - cursorSize.y)
	{
		return true;
	}

	return false;
}
