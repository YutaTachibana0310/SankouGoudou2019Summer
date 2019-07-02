//=====================================
//
//敵の処理 [Enemy.cpp]
//
//Author:馬　前程
//=====================================
#include "Enemy.h"


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
		move.z = -1.0f;
		pos += move;
		//countする
		cntFrame++;
	}

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
void EnemyStraight::Set(D3DXVECTOR3 pos)
{
		//if (!bUse)
		//{
			this->pos = pos;
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
		if (cntFrame > 80 && cntFrame < 150)
		{
			move.z = 0.0f;
		}
		else if (cntFrame >= 150)
		{
			move.z = -1.0f;
		}
		else
		{
			move.z = 1.0f;
		}
		pos += move;
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
void EnemyChange::Set(D3DXVECTOR3 pos)
{
	this->pos = pos;
	bUse = true;
	
}