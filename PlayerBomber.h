//=====================================
//
//プレイヤーヘッダ[player.h]
//Author:GP12B332 12 権頭
//
//=====================================
#ifndef _PLAYERBOMBER_H_
#define _PLAYERBOMBER_H_

#include "main.h"

/**************************************
マクロ定義
***************************************/

/**************************************
構造体定義
***************************************/


/**************************************
プロトタイプ宣言
***************************************/
class PlayerBomber
{
public:
	PlayerBomber();				//コンストラクタ
	~PlayerBomber();				//デストラクタ

	void Init();				//初期化処理
	void Uninit();				//終了処理
	void Update();				//更新処理
	void Draw();				//描画処理

	void Set(D3DXVECTOR3 *pos,D3DXVECTOR3 initpos);
	void CalcBomber(void);


	Transform transform;
	D3DXVECTOR3 *targetPos;
	D3DXVECTOR3 velocity;
	bool active;
	int cntFrame;
	int reachFrame;

	static int instanceCount;

};





#endif