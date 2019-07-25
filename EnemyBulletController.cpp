//=====================================
//
//テンプレート処理[EnemyBulletController.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "EnemyBulletController.h"
#include "EnemyBulletModel.h"
#include "EnemyBullet.h"
#include "Framework\ResourceManager.h"

#include <algorithm>

using namespace std;

/**************************************
マクロ定義
***************************************/
#define ENEMYBULLET_NUM_MAX				(128)
#define ENEMYBULLET_VTX_SIZE			(D3DXVECTOR2(10.0f, 10.0f))
#define ENEMYBULLET_TEX_NAME			("data/TEXTURE/Enemy/EnemyBullet.png")

/**************************************
コンストラクタ
***************************************/
EnemyBulletController::EnemyBulletController()
{
	//リソース作成
	ResourceManager::Instance()->MakePolygon(RESOURCE_ENEMYBULLET_TAG, ENEMYBULLET_TEX_NAME, ENEMYBULLET_VTX_SIZE);
}

/**************************************
デストラクタ
***************************************/
EnemyBulletController::~EnemyBulletController()
{
	for (auto& bullet : modelContainer)
	{
		SAFE_DELETE(bullet);
	}
	modelContainer.clear();
}

/**************************************
終了処理
***************************************/
void EnemyBulletController::Uninit()
{
	for (auto& model : modelContainer)
	{
		model->Uninit();
	}
}

/**************************************
更新処理
***************************************/
void EnemyBulletController::Update()
{
	for (auto& model : modelContainer)
	{
		model->Update();
	}
}

/**************************************
描画処理
***************************************/
void EnemyBulletController::Draw()
{
	GetDevice()->SetRenderState(D3DRS_LIGHTING, false);

	for (auto& model : modelContainer)
	{
		model->Draw();
	}

	GetDevice()->SetRenderState(D3DRS_LIGHTING, true);
}

/**************************************
セット処理
***************************************/
void EnemyBulletController::SetEnemyBullet(vector<D3DXVECTOR3> emitters, LineTrailModel target)
{
	auto itr = find_if(modelContainer.begin(), modelContainer.end(),
		[](EnemyBulletModel* model)
	{
		return !model->active;
	});

	if (itr == modelContainer.end())
	{
		modelContainer.push_back(new EnemyBulletModel());
		itr = modelContainer.end() - 1;
	}

	(*itr)->Init(emitters, target);
}