//=====================================
//
//バックグラウンドシティ処理[BackGroundCity.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "BackGroundCity.h"
#include "Framework\MeshContainer.h"
#include "Framework\Easing.h"
#include "Framework\ResourceManager.h"

/**************************************
マクロ定義
***************************************/
#define BACKGROUNDCITY_INIT_SCALE_Y		(6.0f)
#define BACKGROUNDCITY_INIT_SCALE_XZ	(3.0f)

#define BACKGROUNDCITY_BORDER_Z			(-500.0f)

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/
float BackGroundCity::moveSpeed = 55.0f;
int BackGroundCity::frameFadein = 30;

/**************************************
コンストラクタ
***************************************/
BackGroundCity::BackGroundCity(const char* meshTag)
{
	//メッシュの読み込み
	ResourceManager::Instance()->GetMesh(meshTag, &mesh);

	//スケール初期化
	transform.scale.x = BACKGROUNDCITY_INIT_SCALE_XZ;
	transform.scale.y = BACKGROUNDCITY_INIT_SCALE_Y;
	transform.scale.z = BACKGROUNDCITY_INIT_SCALE_XZ;
}

/**************************************
デストラクタ
***************************************/
BackGroundCity::~BackGroundCity()
{
	mesh = NULL;
}

/**************************************
初期化処理
***************************************/
void BackGroundCity::Init()
{
	cntFrame = 0;
}

/**************************************
終了処理
***************************************/
void BackGroundCity::Uninit()
{

}

/**************************************
更新処理
***************************************/
void BackGroundCity::Update()
{
	transform.pos.z -= moveSpeed;

	//フェードイン
	if (cntFrame < frameFadein)
	{
		cntFrame++;
		alpha = (float)cntFrame / (float)frameFadein;
	}

	//移動
	if (transform.pos.z < BACKGROUNDCITY_BORDER_Z)
	{
		//TODO:マジックナンバー消す
		transform.pos.z += 28800.0f;
		Init();
	}


}

/**************************************
描画処理
***************************************/
void BackGroundCity::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxWorld;

	//ワールド行列設定
	transform.CalcWorldMtx(&mtxWorld);
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	//描画
	mesh->SetMaterialAlpha(alpha);
	mesh->Draw();
}