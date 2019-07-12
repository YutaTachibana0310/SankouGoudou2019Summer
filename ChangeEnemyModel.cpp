//=====================================
//
//ストップエネミーモデル処理[StopEnemyModel.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "ChangeEnemyModel.h"
#include "enemy.h"

/**************************************
マクロ定義
***************************************/
//初期化されてから当たり判定がアクティブになるタイミング
#define STOPENEMY_TIME_COLLIDER_ACTIVATE	(60)

//当たり判定が無効になるタイミング
#define STOPENEMT_TIME_ESCAPE				(300 + STOPENEMY_TIME_COLLIDER_ACTIVATE)

//終了タイミング
#define STOPENEMY_TIME_UNINIT				(60 + STOPENEMT_TIME_ESCAPE)

typedef EnemyModel Base;

/**************************************
構造体定義
***************************************/

/**************************************
コンストラクタ
***************************************/
ChangeEnemyModel::ChangeEnemyModel()
{

}

/**************************************
デストラクタ
***************************************/
ChangeEnemyModel::~ChangeEnemyModel()
{

}

/**************************************
初期化処理
***************************************/
void ChangeEnemyModel::Init(LineTrailModel model)
{
	Base::Init(model);

	cntFrame = 0;
	collider->active = false;

	//とりあえずEnemyを5体生成
	for (int i = 0; i < 5; i++)
	{
		enemyList.push_back(new EnemyChange());
	}

	//EnemyModelに属するEnemyに移動指示を出す
	//TODO:初期位置を変更できるようにする
	D3DXVECTOR3 InitPos = D3DXVECTOR3(0.0f, 500.0f, 250.0f);
	D3DXVECTOR3 edgeL, edgeR;
	model.GetEdgePos(&edgeR, &edgeL);
	edgeL.z = edgeR.z = 250.0f;
	D3DXVECTOR3 offset = (edgeL - edgeR) / ((float)enemyList.size() - 1);

	for (auto& enemy : enemyList)
	{
		enemy->Init();
		enemy->SetVec(InitPos, edgeR, STOPENEMY_TIME_COLLIDER_ACTIVATE, 300, D3DXVECTOR3(0.0f, 15.0f, 0.0));
		edgeR += offset;
	}
}

/**************************************
更新処理
***************************************/
int ChangeEnemyModel::Update()
{
	cntFrame++;

	//60フレーム目で当たり判定をアクティブにする
	if (cntFrame == STOPENEMY_TIME_COLLIDER_ACTIVATE)
		collider->active = true;

	//アクティブになってから300フレームで離脱する
	if (cntFrame == STOPENEMT_TIME_ESCAPE)
		collider->active = false;

	//離脱開始してから60フレームで終了する
	if (cntFrame == STOPENEMY_TIME_UNINIT)
		Uninit();

	for (auto& enemy : enemyList)
	{
		enemy->Update();
	}

	return StateContinuous;
}