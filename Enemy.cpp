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
#include "PlayerBomber.h"

using namespace std;
/**************************************
マクロ定義(命名規則:大きい順)
***************************************/
#define ENEMY_COLLIDER_SIZE	(D3DXVECTOR3(10.0f, 10.0f, 10.0f))
#define CHANGE_FALSE	(300)				//falseの時間(方向が変えってから)
#define SNAKE_FALSE		(900)

#define	ENEMY_ATTENUATION	(0.98f)				//減衰係数 

#define SNAKE_FRAME	(200)

//#define GET_RANDOM(a, b)		((a) + rand() / (RAND_MAX / ((b) - (a) + 1) + 1))

#define STRAIGHT_SCL_MIN	(D3DXVECTOR3(0.0f, 0.0f, 0.0f))  //スケールのアニメーションの最大値	
#define STRAIGHT_SCL_SPEED	(0.01f)							 //アニメーションの時間の増分

#define CHANGE_SCL_MAX		(D3DXVECTOR3(1.0f, 1.0f, 1.0f))
#define CHANGE_SCL_MIN		(D3DXVECTOR3(0.8f, 0.8f, 0.8f))
//#define CHANGE_SCL_SPEED	(0.05f)
#define SNAKE_SCL_MAX		(D3DXVECTOR3(1.0f, 1.0f, 1.0f))
#define SNAKE_SCL_MIN		(D3DXVECTOR3(0.8f, 0.8f, 0.8f))
//#define SNAKE_SCL_SPEED	(0.05f)
#define SCL_MAX				(D3DXVECTOR3(1.0f, 1.0f, 1.0f))
#define SCL_MIN				(D3DXVECTOR3(0.8f, 0.8f, 0.8f))

#define STRAIGHT_WAIT_TIME			(0.9)				//サンプリング周期

#define MIDIUM_ANIMATION_TIME		(3)					//点滅周期

/****************************************
static変数
****************************************/
UINT Enemy::m_InstanceCount;

/****************************************
コンストラクタ
****************************************/
Enemy::Enemy() : 
	m_FlgDestroyed(false)
{
	m_InstanceCount++;
	ResourceManager::Instance()->GetMesh("Enemy", m_pMesh);

	m_Collider = new BoxCollider3D(BoxCollider3DTag::Enemy, &m_Pos);
	m_Collider->SetSize(ENEMY_COLLIDER_SIZE);
	m_Collider->active = true;
	m_Collider->AddObserver(this);
}

/****************************************
デストラクタ
****************************************/
Enemy::~Enemy()
{
	m_InstanceCount--;
	SAFE_DELETE(m_Collider);
}

/****************************************
衝突判定通知レシーバー
****************************************/
void Enemy::OnNotified(BoxCollider3DTag other)
{
	m_FlgDestroyed = true;
	m_Active = false;
}

/****************************************
ボンバー着弾コールバック
****************************************/
void Enemy::OnHitBomber()
{
	m_FlgDestroyed = true;
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
拡大と縮小のアニメーション
****************************************/
int	Enemy::Animation()
{
	//アニメーションを動かすか
	if (!m_AnimationActive)
		return 0;

	if (m_Expansion)
	{
		m_Scl = Easing::EaseValue(m_SclRate,SCL_MIN,
			SCL_MAX, EaseType::Linear);
		m_SclRate += m_SclSpeed;
		if (m_SclRate >= 1.0f)
		{
			m_Expansion = false;
		}
	}
	else
	{
		m_Scl = Easing::EaseValue(m_SclRate, SCL_MIN,
			SCL_MAX, EaseType::Linear);
		m_SclRate -= m_SclSpeed;
		if (m_SclRate <= 0.0f)
		{
			m_Expansion = true;
		}

	}

	return 1;
}

//0903
void Enemy::SetAnimation(bool active,bool expansion, float sclRate,float speed)
{
	m_AnimationActive = active;
	m_Expansion = expansion;
	m_SclRate = sclRate;
	m_SclSpeed = speed;
}

/****************************************
初期化処理
****************************************/
HRESULT  EnemyStraight::VInit(void)
{
	m_PositionHistoryTimer = 0.0f;
	m_PositionHistoryIndex = 0;

	for (int i = 0; i < SHADOW_MAX; i++)
	{
		m_ShadowPos[i] = D3DXVECTOR3(500.0f, 0.0f, 0.0f);
		m_ShadowScl[i] = m_Scl;

	}

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

	m_AnimationActive = false;
	m_Expansion = true;
	m_SclRate = 0.0f;
	m_SclSpeed = 0.0f;
	
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
			m_Pos = Easing::EaseValue(m_CntFrame / m_FrameDest, m_Start,
				m_PosDest, EaseType::InSine);
			
		}
		else
		{
			m_Active = false;
		}

		//アニメーションの処理
		if (!m_AnimationActive)
		{
			//現れる時の拡大
			if(m_SclRate < 1.0f)
			{
				m_Scl = Easing::EaseValue(m_SclRate, STRAIGHT_SCL_MIN,
					D3DXVECTOR3(1.0f, 1.0f, 1.0f), EaseType::OutCubic);
				m_SclRate += STRAIGHT_SCL_SPEED;

				//時間が一気に1.0を超えた場合
				if (m_SclRate >= 1.0f)
				{
					m_Scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
					//次のアニメーションを始める
					SetAnimation(true, false, 1.0f, 0.05f);
				}
			}
		}
		else
		{
			Animation();
		}
		
	}

	if (m_CntFrame > m_PositionHistoryTimer + STRAIGHT_WAIT_TIME)
	{
		m_PositionHistoryTimer = m_CntFrame;
		m_PositionHistoryIndex++;

		if (m_PositionHistoryIndex > SHADOW_MAX - 1)
		{
			m_PositionHistoryIndex = SHADOW_MAX - 1;
			//キュー操作
			for (int i = 1; i < SHADOW_MAX; i++)
			{
				m_ShadowPos[i - 1] = m_ShadowPos[i];
				m_ShadowScl[i - 1] = m_ShadowScl[i];
			}
				
		}
		m_ShadowPos[m_PositionHistoryIndex] = m_Pos;
		m_ShadowScl[m_PositionHistoryIndex] = m_Scl;
	}

	//最後にcountする. 
	m_CntFrame++;
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
		
	}
	m_pMesh->SetMaterialAlpha(1.0f);
}
/****************************************
セット処理
*****************************************/
void EnemyStraight::VSet(D3DXVECTOR3 start, D3DXVECTOR3 end, float frame)
{

	m_FrameDest = frame;
	m_PosDest = end;
	//?
	m_Start = m_Pos = start;
	//m_CntFrame = 0;

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

	m_Active = false;

	m_Scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);

	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_PosDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Start = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_FrameDest = 0.0f;

	m_RotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_CntFrame = 0.0f;

	m_SclRate = 0.0f;
	m_Expansion = true;
	m_AnimationActive = false;
	m_SclSpeed = 0.0f;

	SetAnimation(true,true, 0.0f,0.05f);
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

		if (m_CntFrame > m_FrameDest + m_WaitTime + CHANGE_FALSE)
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
			m_Pos = Easing::EaseValue(m_CntFrame / m_FrameDest, m_Start,
				m_PosDest, EaseType::OutCubic);

		}

		Animation();
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
void EnemyChange::VSet(D3DXVECTOR3 start, D3DXVECTOR3 end, float frame)
{
	//空
}

void EnemyChange::VSetVec(D3DXVECTOR3 start, D3DXVECTOR3 end, float frame, float waitTime, D3DXVECTOR3 vec)
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
	m_Collider->RegisterToCheckList(BoxCollider3DTag::SnakeEnemy);
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
	m_WaitTime = 0.0f;
	m_CurrentIndex = 0;
	m_PosDestMax = 0;
	m_FramePassed = 0.0f;
	m_WaitCount = 0.0f;

	m_Active = false;

	m_Scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_PosDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Start = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_FrameDest = 0.0f;

	m_RotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_CntFrame = 0.0f;

	m_AnimationActive = false;
	m_Expansion = true;
	m_SclRate = 0.0f;
	m_SclSpeed = 0.0f;

	SetAnimation(true, true, 0.0f, 0.05f);
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
	float last = m_FramePassed + m_FrameDestList[m_PosDestMax - 2];

	if (m_Active)
	{
		if (m_CntFrame == last && m_CurrentIndex == m_PosDestMax - 2)
		{
			//そのまま進む
			m_Move = (m_PosDestList[m_PosDestMax - 1] - m_PosDestList[m_PosDestMax - 2]) / SNAKE_FRAME;

		}
		else if (m_CntFrame >= last && m_CurrentIndex == m_PosDestMax - 2)
		{
			//処理が終わったら
			if (m_CntFrame >= last + SNAKE_FALSE)
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
				m_WaitCount = 0.0f;
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

		Animation();
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

		BoxCollider3D::DrawCollider(m_Collider);
	}
}

/****************************************
セット処理
*****************************************/
void EnemySnake::VSet(D3DXVECTOR3 start, D3DXVECTOR3 end1, float frame)
{
	//空
}

void EnemySnake::Set(vector<D3DXVECTOR3> posDestList, vector<float> frameDestList, float waitTime)
{
	m_PosDestList = posDestList;
	m_FrameDestList = frameDestList;
	m_WaitTime = waitTime;

	m_PosDestMax = m_PosDestList.size();

	m_Active = true;
}


//EnemyMidium
/****************************************
コンストラクタ
****************************************/
EnemyMidium::EnemyMidium()
{
	ResourceManager::Instance()->GetMesh("MidiumEnemy", m_pMesh);
}

/****************************************
デストラクタ
****************************************/
EnemyMidium ::~EnemyMidium()
{

}

/****************************************
初期化処理
****************************************/
HRESULT EnemyMidium::VInit()
{
	m_CntFrameNow = 0.0f;
	m_Visible = true;
	m_CntAnim = 0;

	m_Active = false;

	m_Scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_PosDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Start = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_FrameDest = 0.0f;

	m_RotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_CntFrame = 0.0f;

	m_SclRate = 0.0f;
	m_Expansion = true;
	m_AnimationActive = false;
	m_SclSpeed = 0.0f;

	return S_OK;
}

/****************************************
終了処理
*****************************************/
void EnemyMidium::VUninit()
{
	m_Active = false;
}

/****************************************
更新処理
*****************************************/
void EnemyMidium::VUpdate()
{
	if (m_Active)
	{

		m_Pos = Easing::EaseValue(m_CntFrameNow / m_FrameDest, m_Start,
			m_PosDest, EaseType::OutCubic);

		//countする
		m_CntFrameNow++;
		m_CntFrame++;


	}
}

/****************************************
描画処理
*****************************************/
void EnemyMidium::VDraw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;

	//アクティブ&&見える
	if (m_Active&&m_Visible)
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
Move処理(当たるたびに呼び出す)
*****************************************/
void EnemyMidium::Move(D3DXVECTOR3 posDest, float frameDest)
{
	m_PosDest = posDest;
	m_FrameDest = frameDest;
	m_Start = m_Pos;
	//他のラインに移動するたびに、m_CntFrameNowを0に戻す
	m_CntFrameNow = 0.0f;

}

/****************************************
セット処理(最初の設定)
*****************************************/
void EnemyMidium::Set(D3DXVECTOR3 start)
{
	m_Start = start;
	m_Active = true;
}

/****************************************
被弾アニメーション処理
*****************************************/
void EnemyMidium::HitAnimation()
{
	m_CntAnim++;
	if ((m_CntAnim % MIDIUM_ANIMATION_TIME) == 0)
	{
		m_Visible = false;
	}
	else
	{
		m_Visible = true;
	}
	

}

/****************************************
処理
*****************************************/
void EnemyMidium::SetHitAnimation()
{
	m_CntAnim = 0;
}

/****************************************
セット処理
*****************************************/
void EnemyMidium::VSet(D3DXVECTOR3 start, D3DXVECTOR3 end, float frame)
{
	//空
}