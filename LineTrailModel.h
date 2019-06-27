//=====================================
//
//���C���g���C�����f���w�b�_[LineTrailModel.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _LINETRAILMODEL_H_
#define _LINETRAILMODEL_H_

#include "main.h"

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
�g���C���Ɋւ�����������N���X
***************************************/
class LineTrailModel
{
public:
	LineTrailModel();
	LineTrailModel(int start, int end);
	~LineTrailModel();
	int start, end;		//�n�_�A�I�_
	void GetEdgePos(D3DXVECTOR3 *right, D3DXVECTOR3 *left);

	static void CalcEdgePosition();
	static D3DXVECTOR3 GetEdgePos(int i);

private:
	static D3DXVECTOR3 edgePosition[TrailIndexMax];

};
#endif