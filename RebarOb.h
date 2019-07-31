//=============================================================================
//
// モデル処理 [model.h]
// Author : 自分の氏名
//
//=============================================================================
#ifndef _REBAROB_H_
#define _REBAROB_H_


#include "main.h"
#include "TrailCollider.h"
#include "LineTrailModel.h"


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitRebarOb(void);
void UninitRebarOb(void);
void UpdateRebarOb(void);
void DrawRebarOb(void);
void SetRebar(int a,int b);


typedef struct
{
	//ポリゴンXファイルモデル1つ分の情報
	LPDIRECT3DTEXTURE9	m_pD3DTextureRebarob;		// テクスチャへ情報のポインタ
	LPD3DXMESH			m_pD3DXMeshRebarob;		// メッシュ情報へのポインタ
	LPD3DXBUFFER		m_pD3DXBuffMatRebarob;	// マテリアル情報へのポインタ
	DWORD				m_nNumMatRebarob;			// マテリアル情報の数


}REBAROB3D;

typedef struct
{

	D3DXMATRIX			m_mtxWorld;				// ワールドマトリックス

	D3DXVECTOR3			m_posRebarOb;				// モデルの位置
	D3DXVECTOR3			m_rotRebarOb;				// モデルの向き(回転)
	D3DXVECTOR3			m_sclRebarOb;				// モデルの大きさ(スケール)
	D3DXVECTOR3			m_vecRebarOb;             //エネミーのベクトル

	bool                m_bUse;                 //このオブジェクトが使用状態か

	int					m_RebarObID;				// このキャラクタのモデルデータのID
}OBJECT3D;

OBJECT3D* GetRebarOb(int no);//構造体の先頭ポインタを取得
#endif
