//=====================================
//
//プレイヤーヘッダ[player.h]
//Author:GP12B332 12 権頭
//
//=====================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "Framework/MeshContainer.h"

/**************************************
マクロ定義
***************************************/
enum class PlayerState;

/**************************************
プレイヤークラス定義
***************************************/
class Player
{
public:
	MeshContainer* meshPlayer;

	D3DXVECTOR3			pos;				// 現在の位置
	D3DXVECTOR3			move;				// 移動量
	D3DXVECTOR3			scl;				// モデルの大きさ(スケール)
	D3DXVECTOR3			rot;				// 現在の向き
	D3DXVECTOR3			rotDest;			// 目的の向き
	D3DXQUATERNION		Quaternion;

	D3DXVECTOR3			initpos;			// 移動前位置
	D3DXVECTOR3			goalpos;			// 移動後位置
	int					cntFrame;

	PlayerState			CurrentState;


	//関数
	void Init();
	void Uninit();
	void Update();
	void Draw();


	// 移動先確保用のナンバー
	int goal;

};

#endif
