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
	MeshContainer* meshPlayer;

	//いる?
	Enemy();
	virtual ~Enemy();

	bool				active;				//アクティブ

	D3DXVECTOR3			pos;				//現在の位置
	D3DXVECTOR3			move;				//移動量
	D3DXVECTOR3			scl;				//モデルの大きさ(スケール)
	D3DXVECTOR3			rot;				//現在の向き
	D3DXVECTOR3			rotDest;			//目的の向き

	D3DXVECTOR3         dir;				//移動の方向
	D3DXVECTOR3         posDest;			//移動先

	int					cntFrame;			//フレームカウント
	int					frameDest;
	//純粋仮想関数
	virtual HRESULT  Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	virtual void Set(D3DXVECTOR3 start, D3DXVECTOR3 end, int frame) = 0;	//セット処理
	virtual void SetVec(D3DXVECTOR3 start, D3DXVECTOR3 end, int frame, int time, D3DXVECTOR3 vec) {};
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

	void Set(D3DXVECTOR3 start, D3DXVECTOR3 end, int frame);
	
};

class EnemyChange :public Enemy
{
public:

	int m_waitTime;			//停止の時間
	D3DXVECTOR3 vecChange;	//停止して以降のベクトル

	EnemyChange();
	~EnemyChange();
	HRESULT  Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Set(D3DXVECTOR3 start, D3DXVECTOR3 end, int frame);
	void SetVec(D3DXVECTOR3 start, D3DXVECTOR3 end, int frame,int waitTime, D3DXVECTOR3 vec);

};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


#endif
