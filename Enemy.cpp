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



//Enemy
/****************************************
コンストラクタ
****************************************/
//Enemy::Enemy()
//{
//
//}

/****************************************
デストラクタ
****************************************/
//Enemy::~Enemy()
//{
//
//}

//EnemyStraight
/****************************************
コンストラクタ
****************************************/
EnemyStraight::EnemyStraight()
{
	//初期化のコードはコンストラクタに入れる？
}

/****************************************
デストラクタ
****************************************/
EnemyStraight::~EnemyStraight()
{
	//終了処理のコードはデストラクタに入れる？
}

/****************************************
初期化処理
****************************************/
HRESULT  EnemyStraight::Init(void)
{
	bUse = false;
	meshPlayer = new MeshContainer();
	meshPlayer->Load(ENEMY_MODEL);

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
	//SAFE_RELEASE?
	SAFE_DELETE(meshPlayer);
}
/****************************************
更新処理
*****************************************/
void EnemyStraight::Update(void)
{
	if (bUse)	
	{
		//move.y = -1.0f;
		//pos += move;
		
		//((fabsf(pos.x - posDest.x) < 1e-6f) || (fabsf(pos.y - posDest.y) < 1e-6f) || (fabsf(pos.z - posDest.z) < 1e-6f))
		/*double x = D3DXVec3Length(&D3DXVECTOR3(pos - posDest));
		if (!(x< ( (1e-6f))))
		{
			pos += move;
		}*/

		if (cntFrame < frameDest)
		{
			pos += move;
		}

		//countする.
		cntFrame++;
	}
	BeginDebugWindow("posUpdate");
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
	
	if (bUse)
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

		meshPlayer->Draw();
	}
				
}
/****************************************
セット処理
*****************************************/

void EnemyStraight::Set(D3DXVECTOR3 start, D3DXVECTOR3 end,int frame)
{
		//if (!bUse)
		//{
			frameDest = frame;
	        posDest = end;
			pos = start;
			dir = end - start;			
			move = dir /frame;

			bUse = true;
			//pos.x += 10.0f;

		//}




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
	bUse = false;
	meshPlayer = new MeshContainer();
	meshPlayer->Load(ENEMY_MODEL);

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
	//SAFE_RELEASE?
	SAFE_DELETE(meshPlayer);
}
/****************************************
更新処理
*****************************************/
void EnemyChange::Update()
{
	if (bUse)
	{
		if (cntFrame > frameDest && cntFrame <= frameDest + m_waitTime)
		{
			
		}
		else if (cntFrame > frameDest +m_waitTime)
		{
			//move.z = -1.0f;
			move = vecChange;
			pos += move;
		}
		else if (cntFrame < frameDest)
		{
			//move.z = 1.0f;
			
			pos += move;
		}
		BeginDebugWindow("posEnemyChange");
		DebugText("POS:%f,%f,%f", pos.x, pos.y, pos.z);
		DebugText("MOVE:%f,%f,%f", move.x, move.y, move.z);
		EndDebugWindow("pos");
		//countする
		cntFrame++;
	}
	
}
/****************************************
描画処理
*****************************************/
void EnemyChange::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;

	if (bUse)
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

		meshPlayer->Draw();
	}
}

/****************************************
セット処理
*****************************************/
void EnemyChange::Set(D3DXVECTOR3 start, D3DXVECTOR3 end, int frame)
{
	//m_waitTime = waitTime;
	/*frameDest = frame;
	posDest = end;
	pos = start;
	dir = end - start;
	move = dir / frame;

	bUse = true;*/
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

	bUse = true;
}

//void EnemyChange::SetTime(int waitTime)
//{
//	
//	if (bUse)
//	{
//
//		m_waitTime = waitTime;
//	}
//	
//
//}