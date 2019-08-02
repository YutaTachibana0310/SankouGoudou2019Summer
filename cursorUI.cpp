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
Object	cursor;

//=============================================================================
// 初期化処理
//=============================================================================
void Cursor::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	object->LoadTexture(pDevice, ADRESS_TEXTURE_CURSOR, &cursor);
	object->InitialTexture(&cursor);
	object->MakeVertexRotateObject(&cursor);

	cursor.position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	cursor.size		= SIZE_CURSOR;
	cursor.rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	cursor.colliderSize = COLLIDERSIZE_CURSOR / 2;

	object->SetColorObject(&cursor, SET_COLOR_YELLOW);

	// 回転オブジェクト用のサークルを作成
	object->CreateObjectCircle(&cursor, cursor.size.x, cursor.size.y);
}

//=============================================================================
// 終了処理
//=============================================================================
void Cursor::Uninit(void)
{
	object->ReleaseTexture(&cursor);
}

//=============================================================================
// 更新処理
//=============================================================================
void Cursor::Update(HWND hWnd)
{
	cursor.position = GetMousePosition(hWnd);

	for (int i = 0; i < STAR_MAX; i++)
	{
		if (IsStarHitted(i))
		{
			// 選択されているなら
			object->SetColorObject(&cursor, SET_COLOR_RED);
		}
		else
		{	// 元に戻す
			object->SetColorObject(&cursor, SET_COLOR_YELLOW);
		}
	}

	cursor.rotation.z -= SPEED_ROTATION;
}

//=============================================================================
// 描画処理
//=============================================================================
void Cursor::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	object->DrawObject(pDevice, &cursor);
	object->SetVertexRotateObject(&cursor);
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

	if (cursor.position.x + cursor.colliderSize.x > pos.x - size.x 
		&& pos.x + size.x > cursor.position.x - cursor.colliderSize.x 
		&&
		cursor.position.y + cursor.colliderSize.y > pos.y - size.y 
		&& pos.y + size.y > cursor.position.y - cursor.colliderSize.y)
	{
		return true;
	}

	return false;
}
