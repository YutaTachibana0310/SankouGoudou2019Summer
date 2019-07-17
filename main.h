//=============================================================================
//
// メイン処理 [main.h]
// Author : 
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

#define _CRT_SECURE_NO_WARNINGS

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include <windows.h>
#include "d3dx9.h"

#define DIRECTINPUT_VERSION (0x0800)	// 警告対策
#include "dinput.h"
#include "MyLibrary.h"
#include <tchar.h>
#include <stdio.h>
#include <assert.h>

//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************
#if 1	// [ここを"0"にした場合、"構成プロパティ" -> "リンカ" -> "入力" -> "追加の依存ファイル"に対象ライブラリを設定する]
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "dxerr.lib")
#endif

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// ２Ｄポリゴン頂点フォーマット( 頂点座標[2D] / 反射光 / テクスチャ座標 )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
// ３Ｄポリゴン頂点フォーマット( 頂点座標[3D] / 法線 / 反射光 / テクスチャ座標 )
#define	FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

#define SCREEN_WIDTH	(1800)
#define SCREEN_HEIGHT	(1000)

//WQHD用
//#define SCREEN_WIDTH	(1500)
//#define SCREEN_HEIGHT	(900)

#define SCREEN_CENTER_X	(SCREEN_WIDTH / 2)
#define SCREEN_CENTER_Y	(SCREEN_HEIGHT / 2)

#define	NUM_VERTEX		(4)		// 頂点数
#define	NUM_POLYGON		(2)		// ポリゴン数

//解放、削除関連
#define SAFE_RELEASE(p) {if(p){p->Release(); p = NULL;}}
#define SAFE_DELETE(p)	{if(p){delete(p); p = NULL;}}
#define SAFE_DELETE_ARRAY(p)	{if(p){delete[](p); p = NULL;}}

#define TARGETPLAYER_MAX	(2)	//一度に参加できるプレイヤーの最大数

// 上記２Ｄポリゴン頂点フォーマットに合わせた構造体を定義
typedef struct
{
	D3DXVECTOR3 vtx;		// 頂点座標
	float rhw;				// テクスチャのパースペクティブコレクト用
	D3DCOLOR diffuse;		// 反射光
	D3DXVECTOR2 tex;		// テクスチャ座標
} VERTEX_2D;

// 上記３Ｄポリゴン頂点フォーマットに合わせた構造体を定義
typedef struct
{
	D3DXVECTOR3 vtx;		// 頂点座標
	D3DXVECTOR3 nor;		// 法線ベクトル
	D3DCOLOR diffuse;		// 反射光
	D3DXVECTOR2 tex;		// テクスチャ座標
} VERTEX_3D;

//パーティクルの単位頂点
typedef struct
{
	D3DXVECTOR3 vtx;	//頂点座標
	D3DXVECTOR2 tex;	//UV座標
} ParticleUnit;

//SRT情報
typedef struct _Transform
{
	D3DXVECTOR3 pos;	//座標
	D3DXVECTOR3 rot;	//回転
	D3DXVECTOR3 scale;	//スケール

	//コンストラクタ
	_Transform()
	{
		pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	}

	_Transform(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale)
	{
		this->pos = pos;
		this->rot = rot;
		this->scale = scale;
	}

	//回転処理
	void Rotate(float degX, float degY, float degZ)
	{
		rot.x = D3DXToRadian(degX);
		rot.y = D3DXToRadian(degY);
		rot.z = D3DXToRadian(degZ);
	}

}Transform;

//パーティクルのUV情報
typedef struct
{
	float u, v;
}ParticleUV;

typedef struct
{
	D3DXVECTOR3 vtx[4];
	D3DXVECTOR3 nor;
}PLANE;


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LPDIRECT3DDEVICE9 GetDevice(void);
LPDIRECT3DTEXTURE9 CreateTextureFromFile(LPSTR szName, LPDIRECT3DDEVICE9 lpD3DDevice);
void TranslateViewPort(D3DXVECTOR3 *out, D3DXVECTOR3 *pos);
void SetBackColor(D3DXCOLOR color);
int GetCurrentScene(void);
int GetCurrentFPS(void);
LPDIRECT3DTEXTURE9 GetCurrentDrawData();
#endif