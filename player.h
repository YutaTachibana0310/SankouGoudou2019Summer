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
#include "TrailCollider.h"
#include "Framework\BaseObserver.h"
#include "Framework\AnimContainer.h"

/**************************************
マクロ定義
***************************************/
enum PlayerAnimID
{
	Flying,
	Attack,
	PlayerAnimMax
};

/**************************************
プレイヤークラス定義
***************************************/
class Player : public BaseObserver
{
public:
	Player();
	~Player();

	AnimContainer* animation;
	Transform transform;
	TrailCollider *collider;
	float hp;

	bool active;
	int	cntFrame;
	int inputInterval;				//入力間隔

	bool flgInvincible;				//無敵状態
	int cntInvincible;				//無敵フレーム

	D3DXVECTOR3	initpos;			// 移動前位置
	D3DXVECTOR3	goalpos;			// 移動後位置

	IStateMachine<Player> *state;

	//関数
	void ChangeState(IStateMachine<Player> *next);
	void Init();
	void Uninit();
	int Update();
	void Draw();

	void OnNotified(ObserveSubject* notifier);

};

#endif
