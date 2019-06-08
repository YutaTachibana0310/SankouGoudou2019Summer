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
#include "collider.h"
#include "star.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SIZE_X_CURSOR			(40.0f)
#define SIZE_Y_CURSOR			(40.0f)
#define SPEED_ROTATION			(0.10f)

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
	cursor.size = D3DXVECTOR3(SIZE_X_CURSOR, SIZE_Y_CURSOR, 0.0f);
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
// 選択されているかの判定処理 (当たったら選択状態) (*修正予定)
//=============================================================================
bool IsStarHitted(int num, HWND hWnd)
{
	D3DXVECTOR3 starPosition[STAR_MAX];
	GetStarPosition(starPosition);

	// どのスターとも当たってなかったらfalse,それ以外はtrue
	if (IsHittedBB(GetMousePosition(hWnd), starPosition[0],
		D3DXVECTOR2(COLLIDERSIZE_X_STAR, COLLIDERSIZE_Y_STAR),
		D3DXVECTOR2(COLLIDERSIZE_X_CURSOR, COLLIDERSIZE_Y_CURSOR)))
		return true;

	if (IsHittedBB(GetMousePosition(hWnd), starPosition[1],
		D3DXVECTOR2(COLLIDERSIZE_X_STAR, COLLIDERSIZE_Y_STAR),
		D3DXVECTOR2(COLLIDERSIZE_X_CURSOR, COLLIDERSIZE_Y_CURSOR)))
		return true;

	if (IsHittedBB(GetMousePosition(hWnd), starPosition[2],
		D3DXVECTOR2(COLLIDERSIZE_X_STAR, COLLIDERSIZE_Y_STAR),
		D3DXVECTOR2(COLLIDERSIZE_X_CURSOR, COLLIDERSIZE_Y_CURSOR)))
		return true;

	if (IsHittedBB(GetMousePosition(hWnd), starPosition[3],
		D3DXVECTOR2(COLLIDERSIZE_X_STAR, COLLIDERSIZE_Y_STAR),
		D3DXVECTOR2(COLLIDERSIZE_X_CURSOR, COLLIDERSIZE_Y_CURSOR)))
		return true;

	if (IsHittedBB(GetMousePosition(hWnd), starPosition[4],
		D3DXVECTOR2(COLLIDERSIZE_X_STAR, COLLIDERSIZE_Y_STAR),
		D3DXVECTOR2(COLLIDERSIZE_X_CURSOR, COLLIDERSIZE_Y_CURSOR)))
		return true;

	return false;
}