//=====================================
//
//テンプレートヘッダ[debugTimer.h]
//===================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "Framework/MeshContainer.h"


#define PLAYER_INIT_POS		D3DXVECTOR3(0.0 ,-50.0, 150.0)

#define MAX_LENGTH (6)

class Player
{
public:
	int currensState;
	MeshContainer* meshPlayer;

	D3DXVECTOR3			pos;				// 現在の位置
	D3DXVECTOR3			move;				// 移動量
	D3DXVECTOR3			scl;				// モデルの大きさ(スケール)
	D3DXVECTOR3			rot;				// 現在の向き
	D3DXVECTOR3			rotDest;			// 目的の向き
	D3DXQUATERNION		Quaternion;

	D3DXVECTOR3			initpos;			// 移動前位置
	D3DXVECTOR3			goalpos;			// 移動後位置
	int			cntFrame;

	//関数
	void Init();
	void Uninit();
	void Update();
	void Draw();


	/****************************/
	//渡邉さん側にあったメンバ
	/*****************************/
	LPDIRECT3DTEXTURE9		D3DTexturePlayer = NULL;		// テクスチャへのポリゴン

	VERTEX_2D				vertexWk[NUM_VERTEX];				// 頂点情報格納ワーク

	D3DXVECTOR3				posPlayer;						// ポリゴンの移動量
	D3DXVECTOR3				targetpos[MAX_LENGTH];

	// 移動先確保用のナンバー
	int goal;

	HRESULT MakeVertexPlayer(void);
	void SetVertex(void);
};


#endif
