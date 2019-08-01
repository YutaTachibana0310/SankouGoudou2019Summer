//=====================================
//
//エネミーガイドアローヘッダ[EnemyGuideArrow.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _ENEMYGUIDEARROW_H_
#define _ENEMYGUIDEARROW_H_

#include "main.h"
#include "Framework\BoardPolygon.h"
#include <vector>

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class EnemyGuideArrow
{
public:
	EnemyGuideArrow();
	~EnemyGuideArrow();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	Transform transform;
	bool active;

private:
	int cntFrame;
	BoardPolygon *polygon;
};

class EnemyGuideArrowEmitter
{
public:
	EnemyGuideArrowEmitter();
	~EnemyGuideArrowEmitter();

	void Init(D3DXVECTOR3 start, D3DXVECTOR3 end);
	void Uninit();
	void Update();
	void Draw();

	D3DXVECTOR3 start, end;
	bool active;
	Transform transform;

private:
	int cntFrame;
	int cntArrow;
	std::vector<EnemyGuideArrow*> arrowContainer;

};

#endif