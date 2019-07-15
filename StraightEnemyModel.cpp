//=====================================
//
//ストレートエネミーモデル処理[StraightEnemyModel.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "StraightEnemyModel.h"
#include "enemy.h"
#include "Framework\Easing.h"

/**************************************
マクロ定義
***************************************/
typedef EnemyModel Base;

#define STRAIGHTENEMY_REACH_FRAME		(180)

/**************************************
コンストラクタ
***************************************/
StraightEnemyModel::StraightEnemyModel() : StartPosZ(400.0f), DestPosZ(-200.0f)
{

}

/**************************************
デストラクタ
***************************************/
StraightEnemyModel::~StraightEnemyModel()
{

}

/**************************************
初期化処理
***************************************/
void StraightEnemyModel::Init(LineTrailModel model)
{
	Base::Init(model);

	cntFrame = 0;
	collider->active = true;

	//エネミー生成
	for (int i = 0; i < 5; i++)
	{
		enemyList.push_back(new EnemyStraight());
	}

	//Enemyの初期化
	D3DXVECTOR3 edgeR, edgeL;
	model.GetEdgePos(&edgeR, &edgeL);
	edgeL.z = edgeR.z = StartPosZ;
	
	D3DXVECTOR3 offset = (edgeL - edgeR) / ((float)enemyList.size() - 1);
	
	D3DXVECTOR3 dest = edgeR;
	dest.z = DestPosZ;

	for (auto& enemy : enemyList)
	{
		enemy->VInit();
		enemy->VSet(edgeR, dest, STRAIGHTENEMY_REACH_FRAME);
		edgeR += offset;
		dest += offset;
	}

}

/**************************************
更新処理
***************************************/
int StraightEnemyModel::Update()
{
	cntFrame++;
	float t = (float)cntFrame / (float)STRAIGHTENEMY_REACH_FRAME;

	pos.z = Easing<float>::GetEasingValue(t, &StartPosZ, &DestPosZ, EasingType::InCubic);

	if (cntFrame == STRAIGHTENEMY_REACH_FRAME)
	{
		Uninit();
	}

	for (auto& enemy : enemyList)
	{
		enemy->VUpdate();
	}

	return StateContinuous;
}