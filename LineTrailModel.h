//=====================================
//
//ライントレイルモデルヘッダ[LineTrailModel.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _LINETRAILMODEL_H_
#define _LINETRAILMODEL_H_

#include "main.h"
#include <vector>
/**************************************
LineTrailIndex
**************************************/
enum LineTrailIndex
{
	Top,
	MiddleLeft,
	LowerLeft,
	LowerRight,
	MiddleRight,
	TrailIndexMax
};

/**************************************
トレイルに関する情報を扱うクラス
***************************************/
class LineTrailModel
{
public:
	LineTrailModel();
	LineTrailModel(int start, int end);
	~LineTrailModel();
	int start, end;		//始点、終点

	void GetEdgePos(D3DXVECTOR3 *right, D3DXVECTOR3 *left);
	bool operator == (const LineTrailModel& obj) const;
	bool operator != (const LineTrailModel& obj) const;

	static void CalcEdgePosition(std::vector<D3DXVECTOR3>& startPos);
	static D3DXVECTOR3 GetEdgePos(int i);

private:
	static D3DXVECTOR3 edgePosition[TrailIndexMax];

};
#endif