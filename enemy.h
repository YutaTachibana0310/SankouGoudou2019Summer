//=============================================================================
//
//敵の処理 [Enemy.h]
// 
//Author:馬　前程
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "Framework/MeshContainer.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define MAX_ENEMY (100)



//*****************************************************************************
// 種類
//*****************************************************************************


//*****************************************************************************
// クラス定義
//*****************************************************************************
//抽象クラス　さまざまな派生クラスのオブジェクトを一括管理のため
class Enemy
{
public:
	bool bUse;

	
	MeshContainer* meshPlayer;

	/*Enemy();
	virtual ~Enemy();*/
	D3DXVECTOR3			pos;				// 現在の位置
	D3DXVECTOR3			move;				// 移動量
	D3DXVECTOR3			scl;				// モデルの大きさ(スケール)
	D3DXVECTOR3			rot;				// 現在の向き
	D3DXVECTOR3			rotDest;			// 目的の向き

	int					cntFrame;			//フレームカウント
	//純粋仮想関数
	virtual HRESULT  Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	virtual void Set(D3DXVECTOR3 pos) = 0;	//セット処理
};


class EnemyStraight : public Enemy
{
public:

	EnemyStraight();
	~EnemyStraight();
	HRESULT  Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Set(D3DXVECTOR3 pos);
	
};

class EnemyChange :public Enemy
{
public:

	EnemyChange();
	~EnemyChange();
	HRESULT  Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Set(D3DXVECTOR3 pos);
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


#endif
