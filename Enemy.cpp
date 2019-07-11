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

using namespace std;
/**************************************
マクロ定義
***************************************/
#define ENEMY_MODEL  "data/MODEL/airplane000.x"

#define ENEMY_FALSE (300)				//falseの時間(方向が変えってから)

#define	ENEMY_ATTENUATION (0.98f)		//減衰係数 

/****************************************
static変数
****************************************/
MeshContainer* Enemy::m_pMesh;
UINT Enemy::m_InstanceCount;

/****************************************
コンストラクタ
****************************************/
Enemy::Enemy()
{
	m_InstanceCount++;
	if (m_pMesh == NULL)
	{
		m_pMesh = new MeshContainer();
		m_pMesh->Load(ENEMY_MODEL);
	}
}

/****************************************
デストラクタ
****************************************/
Enemy::~Enemy()
{
	m_InstanceCount--;
	if (m_InstanceCount == 0)
	{
		SAFE_DELETE(m_pMesh);
	}
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
	m_Active = false;


	m_Pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scl = D3DXVECTOR3(2.0f, 2.0f, 2.0f);
	m_Rot = D3DXVECTOR3(0.0f, 59.7f, 0.0f);
	m_RotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	m_FrameDest = 0.0f;
	m_Dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_PosDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_CntFrame = 0.0f;
	
	m_Start =  D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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
		if (m_CntFrame <= m_FrameDest )
		{
			//ブレーキの手触り
			m_Pos = Easing<D3DXVECTOR3>::GetEasingValue((m_CntFrame/m_FrameDest), &m_Start, 
				&m_PosDest, EasingType::OutCubic);
			
		}

		
		//countする.
		m_CntFrame++;
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

}
/****************************************
セット処理
*****************************************/

void EnemyStraight::VSet(D3DXVECTOR3 start, D3DXVECTOR3 end, int frame)
{

	m_FrameDest = frame;
	m_PosDest = end;
	
	m_Start = start;
	
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
	m_Active = false;


	m_Pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scl = D3DXVECTOR3(2.0f, 2.0f, 2.0f);
	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_RotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_CntFrame = 0.0f;

	m_FrameDest = 0.0f;
	m_Dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_PosDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_Start = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_waitTime = 0.0f;
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

		if (m_CntFrame > m_FrameDest + m_waitTime + ENEMY_FALSE)
		{
			m_Active = false;
		}

		if (m_CntFrame > m_FrameDest && m_CntFrame < m_FrameDest + m_waitTime)
		{

		}
		else if (m_CntFrame == m_FrameDest + m_waitTime)
		{
			m_Move = m_VecChange;
			
		}
		else if (m_CntFrame > m_FrameDest + m_waitTime)
		{

			//move = vecChange;

			//クオリティアップする?
			m_Move *= ENEMY_ATTENUATION;
			m_Pos += m_Move;
		}
		else if (m_CntFrame < m_FrameDest)
		{
			//ブレーキの手触り
			m_Pos = Easing<D3DXVECTOR3>::GetEasingValue((m_CntFrame / m_FrameDest), &m_Start,
				&m_PosDest, EasingType::OutCubic);
			
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
	m_waitTime = waitTime;
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
	m_Active = false;

	m_CurrentIndex = 0;

	for (int i = 0; i < 5; i++)
	{
		m_PosDestList.push_back(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		m_FrameDestList.push_back(0.0f);
	}
	

	m_Pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scl = D3DXVECTOR3(2.0f, 2.0f, 2.0f);
	m_Rot = D3DXVECTOR3(0.0f, 59.7f, 0.0f);
	m_RotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	m_FrameDest = 0.0f;
	m_Dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_PosDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_CntFrame = 0.0f;

	m_Start = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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
	//前の点を通過するのにの時間
	int framePassed = 0;

	if (m_Active)
	{
		if (m_CntFrame > m_FrameDestList[m_FrameDestList.size() - 1])
		{
			m_Active = false;
		}

		if (m_CntFrame > (framePassed) && m_CntFrame < framePassed + m_WaitTime)
		{

		}//m_WaitTime * (m_CurrentIndex)
		else if ((m_CntFrame == (m_FrameDestList[m_CurrentIndex] + framePassed))
			&& m_CurrentIndex < m_FrameDestList.size())
		{
			//indexを次の点に指定
			m_CurrentIndex++;
			//今までの所要時間
			framePassed = m_CntFrame;
		}
		else //if(m_CurrentIndex < 6)
		{
			m_Pos = Easing<D3DXVECTOR3>::GetEasingValue(((m_CntFrame - framePassed) / m_FrameDestList[m_CurrentIndex]),
				&m_PosDestList[m_CurrentIndex], &m_PosDestList[m_CurrentIndex + 1], EasingType::OutCubic);
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
	}
}

/****************************************
セット処理
*****************************************/
void EnemySnake::VSet(D3DXVECTOR3 start, D3DXVECTOR3 end1, int frame)
{
	//空
}

void EnemySnake::Set(vector<D3DXVECTOR3> posDestList, vector<float> frameDestList,int waitTime)
{
	
	m_PosDestList = posDestList;
	m_FrameDestList = frameDestList;
	m_WaitTime = waitTime;
	m_Active = true;
}