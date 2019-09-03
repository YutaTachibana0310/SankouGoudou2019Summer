//=====================================
//
//ライントレイルモデル処理[LineTrailModel.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "LineTrailModel.h"
#include "starUI.h"

/**************************************
マクロ定義
***************************************/

/**************************************
構造体定義
***************************************/

/**************************************
staticメンバ
***************************************/
D3DXVECTOR3 LineTrailModel::edgePosition[TrailIndexMax];

/**************************************
コンストラクタ
***************************************/
LineTrailModel::LineTrailModel()
{
	start = end = Top;
}

/**************************************
コンストラクタ
***************************************/
LineTrailModel::LineTrailModel(int start, int end)
{
	this->start = start;
	this->end = end;
}

/**************************************
デストラクタ
***************************************/
LineTrailModel::~LineTrailModel()
{

}

/**************************************
==演算子
***************************************/
bool LineTrailModel::operator==(const LineTrailModel& obj) const
{
	if (this->start == obj.start && this->end == obj.end)
		return true;

	if (this->start == obj.end && this->end == obj.start)
		return true;

	return false;
}

/**************************************
!=演算子
***************************************/
bool LineTrailModel::operator!=(const LineTrailModel& obj) const
{
	if (this->start == obj.start && this->end == obj.end)
		return false;

	if (this->start == obj.end && this->end == obj.start)
		return false;

	return true;
}

/**************************************
端点座標取得処理
***************************************/
void LineTrailModel::GetEdgePos(D3DXVECTOR3 *right, D3DXVECTOR3 *left)
{
	if (right != NULL)
		*right = edgePosition[start];
	if (left != NULL)
		*left = edgePosition[end];
}

/**************************************
端点座標取得処理
***************************************/
D3DXVECTOR3 LineTrailModel::GetEdgePos(int i)
{
	return edgePosition[i];
}

/**************************************
端点座標設定処理
***************************************/
void LineTrailModel::CalcEdgePosition(D3DXVECTOR3 *starPos)
{
	const float PositionDistance = 150.0f;
	for (int i = 0; i < STAR_MAX; i++)
	{
		//スターの位置でNear面とFar面を結ぶレイを計算して正規化
		D3DXVECTOR3 nearPos, farPos;
		CalcScreenToWorld(&nearPos, &starPos[i], 0.0f);
		CalcScreenToWorld(&farPos, &starPos[i], 1.0f);

		D3DXVECTOR3 ray = farPos - nearPos;
		D3DXVec3Normalize(&ray, &ray);

		//目標座標を計算
		D3DXVECTOR3 pos = nearPos + ray * PositionDistance;
		edgePosition[i] = pos;
	}
}