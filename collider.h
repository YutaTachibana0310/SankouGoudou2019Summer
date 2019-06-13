//=============================================================================
//
// 当たり判定用処理 [collider.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _COLLIDER_
#define _COLLIDER_

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
bool IsHittedBB(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2);
bool IsHittedBC(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2);

#endif

