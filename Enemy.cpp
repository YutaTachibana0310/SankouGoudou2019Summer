//=====================================
//
//敵の処理 [Enemy.cpp]
//
//Author:馬　前程
//=====================================
#include "Enemy.h"
#include "debugWindow.h"

#include  <math.h>
#include "Framework\Easing.h"
#include "Framework\ResourceManager.h"

using namespace std;

/**************************************
マクロ定義
***************************************/
#define ENEMY_COLLIDER_SIZE	(D3DXVECTOR3(10.0f, 10.0f, 10.0f))
#define ENEMY_FALSE_CHANGE	(300)				//falseの時間(方向が変えってから)
#define ENEMY_FALSE_SNAKE	(900)

#define	ENEMY_ATTENUATION	(0.98f)				//減衰係数 

#define ENEMY_FRAME_SNAKE	(200)

//#define GET_RANDOM(a, b)		((a) + rand() / (RAND_MAX / ((b) - (a) + 1) + 1))

#define STRAIGHT_SCL_MIN	(D3DXVECTOR3(0.0f, 0.0f, 0.0f))  //スケールのアニメーションの最大値	
#define STRAIGHT_SCL_SPEED	(0.01f)							 //アニメーションの時間の増分

#define CHANGE_SCL_MAX		(D3DXVECTOR3(1.0f, 1.0f, 1.0f))
#define CHANGE_SCL_MIN		(D3DXVECTOR3(0.8f, 0.8f, 0.8f))
#define CHANGE_SCL_SPEED	(0.05f)

#define WAIT_TIME			(0.9)							 //サンプリング周期

/****************************************
static変数
****************************************/
UINT Enemy::m_InstanceCount;

/****************************************
コンストラクタ
****************************************/
Enemy::Enemy()
{
	m_InstanceCount++;
	ResourceManager::Instance()->GetMesh("Enemy", &m_pMesh);

	collider = new BoxCollider3D(BoxCollider3DTag::Enemy, &m_Pos);
	collider->SetSize(ENEMY_COLLIDER_SIZE);
	collider->active = true;
}

/****************************************
デストラクタ
****************************************/
Enemy::~Enemy()
{
	m_InstanceCount--;
	SAFE_DELETE(collider);
}

//EnemyStraight
/****************************************
コンストラクタ
****************************************/
EnemyStraight::EnemyStraight()
{

}

/****************************************
デストラクタ
****************************************/
EnemyStraight::~EnemyStraight()
{

}

/****************************************
初期化処理
****************************************/
HRESULT  EnemyStraight::VInit(void)
{
	m_SclTime = 0.0f;

	m_Active = false;

	m_Scl = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_PosDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Start = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_FrameDest = 0.0f;

	m_RotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_CntFrame = 0.0f;

	position_history_timer = 0;
	position_history_index = 0;

	for (int i = 0; i < SHADOW_MAX; i++)
	{
		m_ShadowPos[i] = D3DXVECTOR3(500.0f, 0.0f, 0.0f);
		m_ShadowScl[i] = m_Scl;

	}

	return S_OK;
}
/****************************************
終了処理
*****************************************/
void EnemyStraight::VUninit(void)
{
	m_Active = false;

}

/****************************************
更新処理
*****************************************/
void EnemyStraight::VUpdate(void)
{
	if (m_Active)
	{
		if (m_CntFrame <= m_FrameDest)
		{
			//ブレーキの手触り
			m_Pos = Easing::EaseValue((float)m_CntFrame / m_FrameDest, m_Start,
				m_PosDest, EaseType::InSine);
			
			//現れる時の拡大
			if(m_SclTime < 1.0f)
			{
				m_Scl = Easing::EaseValue(m_SclTime, STRAIGHT_SCL_MIN,
					D3DXVECTOR3(1.0f, 1.0f, 1.0f), EaseType::OutCubic);
				m_SclTime += STRAIGHT_SCL_SPEED;

				//時間が一気に1.0を超えた場合
				if (m_SclTime >= 1.0f)
				{
					m_Scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
				}
			}
		}
		else
		{
			m_Active = false;
		}

		//countする.
		m_CntFrame++;
	}

	if (m_CntFrame > position_history_timer + WAIT_TIME)
	{
		position_history_timer = m_CntFrame;
		position_history_index++;

		if (position_history_index > SHADOW_MAX - 1)
		{
			position_history_index = SHADOW_MAX - 1;
			//キュー操作
			for (int i = 1; i < SHADOW_MAX; i++)
			{
				m_ShadowPos[i - 1] = m_ShadowPos[i];
				m_ShadowScl[i - 1] = m_ShadowScl[i];
			}
				
		}
		m_ShadowPos[position_history_index] = m_Pos;
		m_ShadowScl[position_history_index] = m_Scl;
	}
}

/****************************************
描画処理
*****************************************/
void EnemyStraight::VDraw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;

	if (m_Active)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&mtxWorld);

		// スケールを反映
		D3DXMatrixScaling(&mtxScl, m_Scl.y, m_Scl.x, m_Scl.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Rot.y, m_Rot.x, m_Rot.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, m_Pos.x, m_Pos.y, m_Pos.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
		m_pMesh->Draw();

	}

	for (int n = 0; n < SHADOW_MAX; n++)
	{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&mtxWorld);

		// スケールを反映
		D3DXMatrixScaling(&mtxScl, m_ShadowScl[n].y, m_ShadowScl[n].x, m_ShadowScl[n].z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, m_ShadowPos[n].x, m_ShadowPos[n].y, m_ShadowPos[n].z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

		m_pMesh->SetMaterialAlpha(float(0.07 + n * 0.039));
		m_pMesh->Draw();
		m_pMesh->SetMaterialAlpha(1.0f);
	}

}
/****************************************
セット処理
*****************************************/

void EnemyStraight::VSet(D3DXVECTOR3 start, D3DXVECTOR3 end, int frame)
{

	m_FrameDest = frame;
	m_PosDest = end;

	m_Start = m_Pos = start;
	m_CntFrame = 0;

	m_Active = true;
}


//EnemyChange
/****************************************
コンストラクタ
****************************************/
EnemyChange::EnemyChange()
{

}

/****************************************
デストラクタ
****************************************/
EnemyChange::~EnemyChange()
{

}

/****************************************
初期化処理
****************************************/
HRESULT EnemyChange::VInit(void)
{
	m_WaitTime = 0.0f;
	m_VecChange = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_SclTime = 0.0f;
	m_Expansion = true;
	m_Active = false;


	m_Pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_RotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_CntFrame = 0;

	m_FrameDest = 0;

	m_Dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_PosDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Start = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_FrameDest = 0.0f;

	m_RotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_CntFrame = 0.0f;

	m_VecChange = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	return S_OK;
}
/****************************************
終了処理
*****************************************/
void EnemyChange::VUninit()
{
	m_Active = false;
}

/****************************************
更新処理
*****************************************/
void EnemyChange::VUpdate()
{
	if (m_Active)
	{

		if (m_CntFrame > m_FrameDest + m_WaitTime + ENEMY_FALSE_CHANGE)
		{
			m_Active = false;
		}

		if (m_CntFrame > m_FrameDest && m_CntFrame < m_FrameDest + m_WaitTime)
		{

		}
		else if (m_CntFrame == m_FrameDest + m_WaitTime)
		{
			m_Move = m_VecChange;

		}
		else if (m_CntFrame > m_FrameDest + m_WaitTime)
		{

			//クオリティアップする?
			m_Move *= ENEMY_ATTENUATION;
			m_Pos += m_Move;
		}
		else if (m_CntFrame < m_FrameDest)
		{
			//ブレーキの手触り
			m_Pos = Easing::EaseValue((float)m_CntFrame / m_FrameDest, m_Start,
				m_PosDest, EaseType::OutCubic);

		}

		//拡大と縮小の繰り返し
		if (m_Expansion)
		{
			m_Scl = Easing::EaseValue(m_SclTime, CHANGE_SCL_MIN,
				CHANGE_SCL_MAX, EaseType::Linear);
			m_SclTime += CHANGE_SCL_SPEED;
			if (m_SclTime >= 1.0f)
			{
				m_Expansion = false;
			}
		}
		else
		{
			m_Scl = Easing::EaseValue(m_SclTime, CHANGE_SCL_MIN,
				CHANGE_SCL_MAX, EaseType::Linear);
			m_SclTime -= CHANGE_SCL_SPEED;
			if (m_SclTime <= 0.0f)
			{
				m_Expansion = true;
			}

		}

		//countする
		m_CntFrame++;

	}
}

/****************************************
描画処理
*****************************************/
void EnemyChange::VDraw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;

	if (m_Active)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&mtxWorld);

		// スケールを反映
		D3DXMatrixScaling(&mtxScl, m_Scl.y, m_Scl.x, m_Scl.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Rot.y, m_Rot.x, m_Rot.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, m_Pos.x, m_Pos.y, m_Pos.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

		m_pMesh->Draw();
	}
}

/****************************************
セット処理
*****************************************/
void EnemyChange::VSet(D3DXVECTOR3 start, D3DXVECTOR3 end, int frame)
{
	//空
}

void EnemyChange::VSetVec(D3DXVECTOR3 start, D3DXVECTOR3 end, int frame, int waitTime, D3DXVECTOR3 vec)
{
	m_VecChange = vec;
	m_WaitTime = waitTime;
	m_FrameDest = frame;
	m_PosDest = end;

	m_Start = start;


	m_Active = true;
}



//EnemySnake
/****************************************
コンストラクタ
****************************************/
EnemySnake::EnemySnake()
{
	collider->RegisterToCheckList(BoxCollider3DTag::SnakeEnemy);
}

/****************************************
デストラクタ
****************************************/
EnemySnake::~EnemySnake()
{

}

/****************************************
初期化処理
****************************************/
HRESULT EnemySnake::VInit()
{
	m_WaitTime = 0;
	m_CurrentIndex = 0;
	m_PosDestMax = 0;
	m_FramePassed = 0;
	m_WaitCount = 0;

	m_Active = false;

	m_Pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_Dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_RotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	m_FrameDest = 0;
	m_Dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_PosDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_CntFrame = 0;

	m_Start = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_FrameDest = 0.0f;

	m_RotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_CntFrame = 0.0f;

	return S_OK;
}

/****************************************
終了処理
*****************************************/
void EnemySnake::VUninit()
{
	m_Active = false;
}

/****************************************
更新処理
*****************************************/
void EnemySnake::VUpdate()
{
	//更新前のm_CurrentIndexを保存
	m_PrevIndex = m_CurrentIndex;


	//最後の点のフレーム
	int last = m_FramePassed + m_FrameDestList[m_PosDestMax - 2];

	if (m_Active)
	{
		if (m_CntFrame == last && m_CurrentIndex == m_PosDestMax - 2)
		{
			//そのまま進む
			m_Move = (m_PosDestList[m_PosDestMax - 1] - m_PosDestList[m_PosDestMax - 2]) / ENEMY_FRAME_SNAKE;

		}
		else if (m_CntFrame >= last && m_CurrentIndex == m_PosDestMax - 2)
		{
			//処理が終わったら
			if (m_CntFrame >= last + ENEMY_FALSE_SNAKE)
			{
				m_Active = false;
			}
			m_Pos += m_Move;
		}//停止
		else if ((m_CntFrame > (m_FramePassed + m_FrameDestList[m_CurrentIndex])) && m_CurrentIndex <= m_PosDestMax - 2)
		{
			//停止中のフレームを一時保存する
			m_WaitCount++;
			//停止の時間が過ぎたら
			if (m_WaitCount == m_WaitTime)
			{
				//停止の時間をカウンターに入れる
				m_FramePassed = m_CntFrame;
				m_WaitCount = 0;
			}
		}//次の点に着いたら
		else if ((m_CntFrame == (m_FramePassed + m_FrameDestList[m_CurrentIndex])) && m_CurrentIndex <= m_PosDestMax - 2)
		{
			//indexを次の点に指定
			m_CurrentIndex++;
			//今までの所要時間を記録
			m_FramePassed = m_CntFrame;
		}
		else if (m_CurrentIndex <= m_PosDestMax - 2)
		{
			m_Pos = Easing::EaseValue((float(m_CntFrame - m_FramePassed) / m_FrameDestList[m_CurrentIndex]),
				m_PosDestList[m_CurrentIndex], m_PosDestList[m_CurrentIndex + 1], EaseType::OutCubic);
		}

		//countする
		m_CntFrame++;

	}
}

/****************************************
描画処理
*****************************************/
void EnemySnake::VDraw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;

	if (m_Active)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&mtxWorld);

		// スケールを反映
		D3DXMatrixScaling(&mtxScl, m_Scl.y, m_Scl.x, m_Scl.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Rot.y, m_Rot.x, m_Rot.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, m_Pos.x, m_Pos.y, m_Pos.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

		m_pMesh->Draw();

		BoxCollider3D::DrawCollider(collider);
	}
}

/****************************************
セット処理
*****************************************/
void EnemySnake::VSet(D3DXVECTOR3 start, D3DXVECTOR3 end1, int frame)
{
	//空
}

void EnemySnake::Set(vector<D3DXVECTOR3> posDestList, vector<int> frameDestList, int waitTime)
{
	m_PosDestList = posDestList;
	m_FrameDestList = frameDestList;
	m_WaitTime = waitTime;

	m_PosDestMax = m_PosDestList.size();

	m_Active = true;
}