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
#define BACKGROUNDCITY_INIT_SCALE_Y		(15.0f)
#define BACKGROUNDCITY_INIT_SCALE_XZ	(5.5f)

#define BACKGROUNDCITY_BORDER_Z			(-500.0f)

#define BACKGROUNDCITY_POSY_MIN			(-15)
#define BACKGROUNDCITY_POSY_MAX			(-10)
#define BACKGROUNDCITY_POSY_MAGNI		(200.0f);

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/
float BackGroundCity::moveSpeed = 75.0f;
int BackGroundCity::frameFadein = 300;
float BackGroundCity::depthMaxZ = 0.0f;

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

	transform.Rotate(0.0f, 45.0f * RandomRange(0, 8), 0.0f);

	transform.pos.y = RandomRange(BACKGROUNDCITY_POSY_MIN, BACKGROUNDCITY_POSY_MAX) * BACKGROUNDCITY_POSY_MAGNI;
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
		transform.pos.z += depthMaxZ;
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
	//mesh->SetMaterialAlpha(alpha);
	mesh->Draw();
}