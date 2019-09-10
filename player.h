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
#include "BomberStockEffect.h"
#include "Framework\ColliderObserver.h"

class BoxCollider3D;
/**************************************
マクロ定義
***************************************/
enum PlayerAnimID
{
	Flying,
	Attack,
	FireBomber,
	FallDown,
	PlayerAnimMax
};

/**************************************
プレイヤークラス定義
***************************************/
class Player : public BaseObserver, ColliderObserver
{
public:
	Player();
	~Player();

	Transform transform;
	TrailCollider *collider;

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
	void ChangeAnim(PlayerAnimID next);
	void ReturnPrevAnim();
	void Init();
	void Uninit();
	int Update();
	void Animation();
	void Draw();

	void OnNotified(ObserveSubject* notifier);
	void ChargeBomber();
	void StockBomber();
	void OnNotified(BoxCollider3DTag other) override;

	void EnableCollider(bool state);
	bool IsAlive();
	float GetHp();

	static const float MaxHp;

private:
	AnimContainer* animation;
	BomberStockEffect* stockEffect;
	BoxCollider3D *boxCollider;
	float hp;
	PlayerAnimID currentAnim, prevAnim;

	const float DamageValue = MaxHp / 4.0f;

	static const float AnimShiftTime[PlayerAnimID::PlayerAnimMax];
	static const D3DXVECTOR3 CameraShakeAmplitude;
	static const int CameraShakeDuration;
};

#endif
