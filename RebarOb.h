//=============================================================================
//
// モデル処理 [model.h]
// Author : 自分の氏名
//
//=============================================================================
#ifndef _REBAROB_H_
#define _REBAROB_H_

#include "main.h"
#include "TrailCollider.h"
#include "LineTrailModel.h"
#include "Framework\MeshContainer.h"
#include "Framework\Easing.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class RebarObstacle
{
public:
	RebarObstacle(const D3DXVECTOR3& pos, LineTrailModel& model);
	~RebarObstacle();

	void Update();
	void Draw();
	void Move(const D3DXVECTOR3& offset, int duration, EaseType type);
	void Move(const Transform& target, float length, int duration, EaseType type);

	bool IsDestroyed();

private:
	int cntFrame;
	bool isDestroyed;
	bool reserveDestroy;

	Transform* transform;
	TrailCollider* collider;

	MeshContainer *mesh;

	D3DXVECTOR3 rotateAxis;

	D3DXVECTOR3 startPos, endPos;
	int moveDuration;
	EaseType moveEaseType;
	bool inMoving;

	void _Move();
};


#endif
