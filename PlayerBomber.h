//=====================================
//
//プレイヤーボンバーヘッダ[PlayerBomber.h]
//Author:GP12B332 12 権頭
//
//=====================================
#ifndef _PLAYERBOMBER_H_
#define _PLAYERBOMBER_H_

#include "main.h"
#include "Framework\BoxCollider3D.h"
#include "enemy.h"
#include "BossEnemyModel.h"

/**************************************
マクロ定義
***************************************/

/**************************************
構造体定義
***************************************/

/**************************************
プロトタイプ宣言
***************************************/
class PlayerBomber : public ColliderObserver
{
public:
	PlayerBomber();						//コンストラクタ
	virtual ~PlayerBomber();			//デストラクタ

	//初期化処理
	void Init(const D3DXVECTOR3& moveDir);
	void Uninit();				//終了処理
	virtual void Update() = 0;	//更新処理
	void Draw();				//描画処理

	void Homing(void);
	void OnNotified(BoxCollider3DTag other);

	bool active;

protected:
	Transform transform;
	D3DXVECTOR3 targetPos;
	D3DXVECTOR3 velocity;
	int cntFrame;
	int reachFrame;

	static int instanceCount;

	void Set(D3DXVECTOR3 initPos);

private:
	BoxCollider3D* collider;

};

#endif