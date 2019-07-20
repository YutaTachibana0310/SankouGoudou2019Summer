//=====================================
//
//バックグラウンドコントローラ処理[BackGroundController.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "BackGroundController.h"
#include "BackGroundCity.h"
#include "SkyBox.h"

#include "Framework\ResourceManager.h"

using namespace std;

/**************************************
マクロ定義
***************************************/
#define BACKGROUND_CITY_KIND_MAX		(3)		//背景モデルの種類
#define BACKGROUND_CITY_NUMMAX_X		(6)		//
#define BACKGROUND_CITY_NUMMAX_Z		(16)	//

//読み込むXファイル
static const char* MeshFileName[] = {
	"data/MODEL/City/city01.x",
	"data/MODEL/City/city02.x",
	"data/MODEL/City/city03.x"
};

//背景メッシュのタグ
static const char* MeshTag[] = {
	"city01",
	"city02",
	"city03"
};

/**************************************
コンストラクタ
***************************************/
BackGroundController::BackGroundController()
{
	//背景モデル読み込み
	for (int i = 0; i < BACKGROUND_CITY_KIND_MAX; i++)
	{
		ResourceManager::Instance()->LoadMesh(MeshTag[i], MeshFileName[i]);
	}

	//CityContainer作成
	CreateCityContainer();

	//スカイボックス作成
	skyBoxies.push_back(new SkyBox(D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f), D3DXVECTOR2(6.0f, 6.0f)));
	skyBoxies[0]->LoadTexture("data/TEXTURE/BG/img_post152_07.jpg");
}

/**************************************
デストラクタ
***************************************/
BackGroundController::~BackGroundController()
{
	for (auto& city : cityContainer)
	{
		SAFE_DELETE(city);
	}
	cityContainer.clear();

	for (auto& skybox : skyBoxies)
	{
		SAFE_DELETE(skybox);
	}
	skyBoxies.clear();
}

/**************************************
初期化処理
***************************************/
void BackGroundController::Init()
{
	for (auto& city : cityContainer)
	{
		city->Init();
	}
}

/**************************************
終了処理
***************************************/
void BackGroundController::Uninit()
{
	for (auto& city : cityContainer)
	{
		city->Uninit();
	}
}

/**************************************
更新処理
***************************************/
void BackGroundController::Update()
{
	for (auto& city : cityContainer)
	{
		city->Update();
	}

	for (auto &box : skyBoxies)
	{
		box->Update();
	}
}

/**************************************
描画処理
***************************************/
void BackGroundController::Draw()
{
	for (auto& box : skyBoxies)
	{
		box->Draw();
	}

	for (auto& city : cityContainer)
	{
		city->Draw();
	}
}

/**************************************
シティコンテナ作成処理
***************************************/
void BackGroundController::CreateCityContainer()
{
	const float BasePosX = 2000.0f;
	const float OffsetX = 3000.0f;
	const float OffsetZ = 3000.0f;

	//背景のCityを作成
	cityContainer.resize(BACKGROUND_CITY_NUMMAX_X * BACKGROUND_CITY_NUMMAX_Z);
	for (auto& city : cityContainer)
	{
		int index = RandomRange(0, BACKGROUND_CITY_KIND_MAX);
		city = new BackGroundCity(MeshTag[index]);
	}

	//左手側のCityを作成
	int cityIndex = 0;
	for (int i = 0; i < BACKGROUND_CITY_NUMMAX_Z; i++)
	{
		for (int j = 0; j < BACKGROUND_CITY_NUMMAX_X / 2; j++)
		{
			cityContainer[cityIndex]->transform.pos.x = BasePosX + OffsetX * j;
			cityContainer[cityIndex]->transform.pos.z = OffsetZ * i;
			cityIndex++;
		}
	}

	//右手側のCityを作成
	for (int i = 0; i < BACKGROUND_CITY_NUMMAX_Z; i++)
	{
		for (int j = 0; j < BACKGROUND_CITY_NUMMAX_X / 2; j++)
		{
			cityContainer[cityIndex]->transform.pos.x = -BasePosX - OffsetX * j;
			cityContainer[cityIndex]->transform.pos.z = OffsetZ * i;
			cityIndex++;
		}
	}

	//Cityの奥行き最大値を設定
	BackGroundCity::depthMaxZ = BACKGROUND_CITY_NUMMAX_Z * OffsetZ;
}