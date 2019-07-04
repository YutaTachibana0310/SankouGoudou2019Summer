//=====================================
//
//敵の処理 [Enemy.cpp]
//
//Author:馬　前程
//=====================================
#include "Enemy.h"

#include "debugWindow.h"

#include  <math.h>


/**************************************
マクロ定義
***************************************/
//#define ENEMY_NUM (4) //1グループのキューブ(エネミー)の量
#define ENEMY_MODEL  "data/MODEL/airplane000.x"

#define ENEMY_FALSE (300)	//falseの時間(方向が変えってから)

/****************************************
static変数
****************************************/
MeshContainer* Enemy::mesh;
UINT Enemy::instanceCount;

/****************************************
コンストラクタ
****************************************/
Enemy::Enemy()
{
	instanceCount++;
	if (mesh == NULL)
	{
		mesh = new MeshContainer();
		mesh->Load(ENEMY_MODEL);
	}
}

/****************************************
デストラクタ
****************************************/
Enemy::~Enemy()
{
	instanceCount--;
	if (instanceCount == 0)
	{
		SAFE_DELETE(mesh);
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
HRESULT  EnemyStraight::Init(void)
{
	active = false;
	

	pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scl = D3DXVECTOR3(2.0f, 2.0f, 2.0f);
	rot = D3DXVECTOR3(0.0f, 59.7f, 0.0f);
	rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	

	frameDest = 0;
	dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	posDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	cntFrame = 0;
	return S_OK;
}
/****************************************
終了処理
*****************************************/
void EnemyStraight::Uninit(void)
{
	
	
}
/****************************************
更新処理
*****************************************/
void EnemyStraight::Update(void)
{
	if (active)	
	{
		if (cntFrame < frameDest)
		{
			pos += move;
		}

		//countする.
		cntFrame++;
	}
	BeginDebugWindow("posEnemyStraight");
	DebugText("POS:%f,%f,%f",pos.x,pos.y,pos.z);
	DebugText("MOVE:%f,%f,%f", move.x, move.y, move.z);
	EndDebugWindow("pos");
}

/****************************************
描画処理
*****************************************/
void EnemyStraight::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;
	
	if (active)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&mtxWorld);

		// スケールを反映
		D3DXMatrixScaling(&mtxScl, scl.y, scl.x, scl.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, pos.x, pos.y, pos.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

		mesh->Draw();
	}
				
}
/****************************************
セット処理
*****************************************/

void EnemyStraight::Set(D3DXVECTOR3 start, D3DXVECTOR3 end,int frame)
{
		
	frameDest = frame;
	posDest = end;
	pos = start;
	dir = end - start;
	move = dir / frame;

	active = true;
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
HRESULT EnemyChange::Init(void)
{
	active = false;
	

	pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scl = D3DXVECTOR3(2.0f, 2.0f, 2.0f);
	rot = D3DXVECTOR3(0.0f, 59.7f, 0.0f);
	rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	cntFrame = 0;

	frameDest = 0;
	dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	posDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	return S_OK;
}
/****************************************
終了処理
*****************************************/
void EnemyChange::Uninit()
{
	
	
}
/****************************************
更新処理
*****************************************/
void EnemyChange::Update()
{
	if (active)
	{

		if (cntFrame > frameDest + m_waitTime + ENEMY_FALSE)
		{
			active = false;
		}

		if (cntFrame > frameDest && cntFrame <= frameDest + m_waitTime)
		{
			
		}
		else if (cntFrame > frameDest +m_waitTime)
		{
		
			move = vecChange;
			pos += move;
		}
		else if (cntFrame < frameDest)
		{
			pos += move;

		}
		//countする
		cntFrame++;
	}

	BeginDebugWindow("posEnemyChange");
	DebugText("POS:%f,%f,%f", pos.x, pos.y, pos.z);
	DebugText("MOVE:%f,%f,%f", move.x, move.y, move.z);
	DebugText("ACTIVE:%d", active);
	EndDebugWindow("pos");
	
}
/****************************************
描画処理
*****************************************/
void EnemyChange::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;

	if (active)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&mtxWorld);

		// スケールを反映
		D3DXMatrixScaling(&mtxScl, scl.y, scl.x, scl.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, pos.x, pos.y, pos.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

		mesh->Draw();
	}
}

/****************************************
セット処理
*****************************************/
void EnemyChange::Set(D3DXVECTOR3 start, D3DXVECTOR3 end, int frame)
{
	//空
}

void EnemyChange::SetVec(D3DXVECTOR3 start, D3DXVECTOR3 end, int frame,  int waitTime,D3DXVECTOR3 vec)
{
	vecChange = vec;
	m_waitTime = waitTime;
	frameDest = frame;
	posDest = end;
	pos = start;
	dir = end - start;
	move = dir / frame;

	active = true;
}

