//=============================================================================
//
// モデル処理 [model.h]
// Author : 自分の氏名
//
//=============================================================================
#ifndef _REBAROB_H_
#define _REBAROB_H_


#include "main.h"



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitRebarOb(void);
void UninitRebarOb(void);
void UpdateRebarOb(void);
void DrawRebarOb(void);
void ResetRebar(int no);
void SetRebar(D3DXVECTOR3 pos);


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

	D3DXVECTOR3			m_DirSpeed;				//移動ベクトル
	D3DXVECTOR3			m_RotSpeed;				//回転スピード
	D3DXVECTOR3			m_Kakudo;				//回転移動用角度
	D3DXVECTOR3			m_Radius;				//回転移動用半径

	bool                m_bUse;                 //このオブジェクトが使用状態か

	int					m_RebarObID;				// このキャラクタのモデルデータのID
	int					m_ShadowID;				// このキャラクタの影オブジェクトのID
}OBJECT3D;

OBJECT3D* GetRebarOb(int no);//構造体の先頭ポインタを取得
#endif
