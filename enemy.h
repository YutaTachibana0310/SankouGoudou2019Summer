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
#include "Framework\BoxCollider3D.h"
#include "Framework\ColliderObserver.h"
#include <vector>

using namespace std;
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SHADOW_MAX      (8)						//シャドウ数

//*****************************************************************************
// 種類
//*****************************************************************************
class PlayerBomber;

//*****************************************************************************
// クラス定義
//*****************************************************************************
//抽象クラス　さまざまな派生クラスのオブジェクトを一括管理のため
class Enemy : public ColliderObserver
{
public:
	
	Enemy();
	virtual ~Enemy();

	bool				m_Active;			//アクティブ

	D3DXVECTOR3			m_Scl;				//モデルの大きさ(スケール)
	D3DXVECTOR3			m_Rot;				//現在の向き
	D3DXVECTOR3			m_Pos;				//現在の位置

	D3DXVECTOR3			m_Move;				//移動量
	D3DXVECTOR3         m_Dir;				//移動の方向
	D3DXVECTOR3         m_PosDest;			//移動先
	D3DXVECTOR3         m_Start;			//移動の元
	float				m_FrameDest;	    //移動がいるフレーム数

	D3DXVECTOR3			m_RotDest;			//目的の向き
	float				m_CntFrame;			//フレームカウント

	//アニメーション
	bool				m_AnimationActive;	//アニメーションを動かすか
	bool                m_Expansion;		//拡大か縮小か
	float				m_SclRate;			//スケールの割合
	float				m_SclSpeed;			//スケールの増分
	
	bool				m_FlgDestroyed;		//撃破判定
	void OnNotified(BoxCollider3DTag other);//衝突判定通知レシーバー
	void OnHitBomber();						//ボンバー着弾時のコールバック

	//純粋仮想関数
	virtual HRESULT  VInit(void) = 0;
	virtual void VUninit(void) = 0;
	virtual void VUpdate(void) = 0;
	virtual void VDraw(void) = 0;
	virtual void VSet(D3DXVECTOR3 start, D3DXVECTOR3 end, float frame) = 0;	//セット処理

	virtual void VSetVec(D3DXVECTOR3 start, D3DXVECTOR3 end, float frame, float time, D3DXVECTOR3 vec) {};
	int Animation();

	//アニメーション
	void SetAnimation(bool active, bool expansion, float sclRate,float speed);

	//staticメンバ
	MeshContainer *m_pMesh;
	static UINT m_InstanceCount;

protected:
	BoxCollider3D* m_Collider;
};

class EnemyStraight : public Enemy
{
public:
	//float			m_SclRate;								//アニメーションの時間

	float			m_PositionHistoryTimer;					//直前のフレームの時間
	int				m_PositionHistoryIndex;					//シャドウワークのインデクス

	D3DXVECTOR3		m_ShadowPos[SHADOW_MAX];	            //キュー構造		
	D3DXVECTOR3		m_ShadowScl[SHADOW_MAX];

	EnemyStraight();
	~EnemyStraight();
	HRESULT  VInit(void);
	void VUninit(void);
	void VUpdate(void);
	void VDraw(void);

	void VSet(D3DXVECTOR3 start, D3DXVECTOR3 end, float frame);
	
};

class EnemyChange :public Enemy
{
public:

	float			m_WaitTime;		//停止の時間
	D3DXVECTOR3		m_VecChange;	//停止して以降のベクトル
	
	EnemyChange();
	~EnemyChange();
	HRESULT  VInit(void);
	void VUninit(void);
	void VUpdate(void);
	void VDraw(void);

	void VSetVec(D3DXVECTOR3 start, D3DXVECTOR3 end, float frame,float waitTime, D3DXVECTOR3 vec);
	void VSet(D3DXVECTOR3 start, D3DXVECTOR3 end, float frame);

};

class EnemySnake :public Enemy
{
public:
	float			m_WaitTime;						//停止の時間
	int				m_CurrentIndex;					//現在、posDestListの何番へ向かっているかを入れる変数
	int				m_PrevIndex;					//1フレーム前はposDestListの何番へ向かっていたか
	int				m_PosDestMax;					//m_FrameDestListの要素数
	float			m_FramePassed;					//前の点を通過するのにの時間
	float			m_WaitCount;					//停止状態のフレームをカウント
	UINT			m_currentColliderID;			//現在所属しているコライダーのID

	vector<D3DXVECTOR3> m_PosDestList;              //移動先、m_PosDestList[0]はEからカウント
	vector<float>	    m_FrameDestList;		    //移動がいるフレーム数　m_PosDestList[1]にいる時、 m_FrameDestList[0]

	EnemySnake();
	~EnemySnake();

	HRESULT VInit(void);
	void VUninit(void);
	void VUpdate(void);
	void VDraw(void);

	//スタートの所(posDestList[0])　
	//[1]移動先ごとに設定、[2]posDestListの何番の移動がいるフレーム数に設定、[3]停止の時間
	void Set(vector<D3DXVECTOR3> posDestList, vector<float> m_frameDestList,float m_waitTime);

	void VSet(D3DXVECTOR3 start, D3DXVECTOR3 end, float frame);
	
};

class EnemyMidium : public Enemy
{
public:
	float		m_CntFrameNow;			//フレームカウント(今回の移動が経った時間)
	bool		m_Visible;				//EnemyMidiumが見えるか
	int			m_CntAnim;				//アニメーションカウント
	
	EnemyMidium();
	~EnemyMidium();
	HRESULT VInit(void);
	void VUninit(void);
	void VUpdate(void);
	void VDraw(void);

	void Move(D3DXVECTOR3 posDest, float frameDest);
	void Set(D3DXVECTOR3 start);

	void HitAnimation();
	void SetHitAnimation();

	void VSet(D3DXVECTOR3 start, D3DXVECTOR3 end, float frame);
	
};
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


#endif
