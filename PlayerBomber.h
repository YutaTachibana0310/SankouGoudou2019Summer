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
	PlayerBomber();				//コンストラクタ
	~PlayerBomber();			//デストラクタ

	//初期化処理
	void Init(const D3DXVECTOR3& moveDir);
	void Uninit();				//終了処理
	void Update();				//更新処理
	void Draw();				//描画処理

	void Set(D3DXVECTOR3 pos,D3DXVECTOR3 initpos);
	void CalcBomber(void);
	void OnNotified(BoxCollider3DTag other);

	Transform transform;
	D3DXVECTOR3 targetPos;
	D3DXVECTOR3 velocity;
	bool active;
	int cntFrame;
	int reachFrame;

	static int instanceCount;

private:
	BoxCollider3D* collider;

};





#endif