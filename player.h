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
#include "PlayerTrail.h"
#include "IStateMachine.h"
#include <functional>

/**************************************
マクロ定義
***************************************/


/**************************************
プレイヤークラス定義
***************************************/
class Player
{
public:
	Player();
	~Player();

	MeshContainer* mesh;
	Transform transform;

	bool active;
	int	cntFrame;

	D3DXVECTOR3	initpos;			// 移動前位置
	D3DXVECTOR3	goalpos;			// 移動後位置

	IStateMachine<Player> *state;
	PlayerTrail *trail;

	//関数
	void ChangeState(IStateMachine<Player> *next);
	void Init();
	void Uninit();
	int Update();
	void Draw();
};

#endif
