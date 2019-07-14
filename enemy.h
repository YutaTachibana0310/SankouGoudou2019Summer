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
#include <vector>

using namespace std;
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
	

	
	Enemy();
	virtual ~Enemy();

	bool				m_Active;				//アクティブ

	D3DXVECTOR3			m_Pos;				//現在の位置
	D3DXVECTOR3			m_Move;				//移動量
	D3DXVECTOR3			m_Scl;				//モデルの大きさ(スケール)
	D3DXVECTOR3			m_Rot;				//現在の向き
	D3DXVECTOR3			m_RotDest;			//目的の向き

	D3DXVECTOR3         m_Dir;				//移動の方向
	D3DXVECTOR3         m_PosDest;			//移動先

	float				m_CntFrame;			//フレームカウント

	D3DXVECTOR3         m_Start;			//移動の元

	float					m_FrameDest;	//移動がいるフレーム数
	//純粋仮想関数
	virtual HRESULT  VInit(void) = 0;
	virtual void VUninit(void) = 0;
	virtual void VUpdate(void) = 0;
	virtual void VDraw(void) = 0;
	virtual void VSet(D3DXVECTOR3 start, D3DXVECTOR3 end, int frame) = 0;	//セット処理
	virtual void VSetVec(D3DXVECTOR3 start, D3DXVECTOR3 end, int frame, int time, D3DXVECTOR3 vec) {};

	//staticメンバ
	static MeshContainer *m_pMesh;
	static UINT m_InstanceCount;
};

class EnemyStraight : public Enemy
{
public:

	EnemyStraight();
	~EnemyStraight();
	HRESULT  VInit(void);
	void VUninit(void);
	void VUpdate(void);
	void VDraw(void);

	void VSet(D3DXVECTOR3 start, D3DXVECTOR3 end, int frame);
	
};

class EnemyChange :public Enemy
{
public:

	int m_waitTime;				//停止の時間
	D3DXVECTOR3 m_VecChange;	//停止して以降のベクトル

	EnemyChange();
	~EnemyChange();
	HRESULT  VInit(void);
	void VUninit(void);
	void VUpdate(void);
	void VDraw(void);

	void VSet(D3DXVECTOR3 start, D3DXVECTOR3 end, int frame);
	void VSetVec(D3DXVECTOR3 start, D3DXVECTOR3 end, int frame,int waitTime, D3DXVECTOR3 vec);

};

class EnemySnake :public Enemy
{
public:
	int m_WaitTime;						//停止の時間
	int m_CurrentIndex;					//現在、posDestListの何番へ向かっているかを入れる変数
	int m_posDestMax;					//m_FrameDestListの要素数

	vector<D3DXVECTOR3> m_PosDestList;  //移動先、仕様書のイメージ図と違う、m_PosDestList[0]はEからカウント
	vector<float> m_FrameDestList;		//移動がいるフレーム数　m_PosDestList[1]にいる時、 m_FrameDestList[0]

	EnemySnake();
	~EnemySnake();

	HRESULT VInit(void);
	void VUninit(void);
	void VUpdate(void);
	void VDraw(void);

	void VSet(D3DXVECTOR3 start, D3DXVECTOR3 end, int frame);

	//スタートの所(posDestList[0])　
	//[1]移動先ごとに設定、[2]posDestListの何番の移動がいるフレーム数に設定、[3]停止の時間
	void Set(vector<D3DXVECTOR3> posDestList, vector<float> m_frameDestList,int m_waitTime);
	
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


#endif
