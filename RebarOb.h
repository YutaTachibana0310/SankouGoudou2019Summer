//=============================================================================
//
// モデル処理 [model.h]
// Author : 自分の氏名
//
//=============================================================================
#ifndef _REBAROB_H_
#define _REBAROB_H_

#include "main.h"
#include "Framework\BoxCollider3D.h"
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
	RebarObstacle(const D3DXVECTOR3& pos, LineTrailModel& model, const Transform& player);
	~RebarObstacle();

	void Update();
	void Draw();
	void Move(const D3DXVECTOR3& offset, int duration, EaseType type);
	void Move(float length, int duration, EaseType type, int delay);

	bool IsDestroyed();

private:
	int cntFrame;
	bool isDestroyed;
	bool reserveDestroy;
	int delay;

	Transform* transform;
	BoxCollider3D* collider;

	MeshContainer *mesh;

	D3DXVECTOR3 rotateAxis;

	D3DXVECTOR3 startPos, endPos;
	int moveDuration;
	EaseType moveEaseType;
	bool inMoving;
	const Transform& player;
	float moveLength;

	void _Move();
};


#endif
