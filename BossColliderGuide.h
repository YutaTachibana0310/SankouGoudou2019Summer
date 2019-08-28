//=====================================
//
//ボスコライダーガイドヘッダ[BossColliderGuide.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BOSSCOLLIDERGUIDE_H_
#define _BOSSCOLLIDERGUIDE_H_

#include "main.h"
#include "Framework\BoardPolygon.h"
#include "LineTrailModel.h"

/**************************************
前方宣言
***************************************/
class BossColliderLine;
class BossColliderEdge;

/**************************************
マクロ・列挙子定義
***************************************/

/**************************************
クラス定義
***************************************/
class BossColliderGuide
{
public:
	BossColliderGuide(LineTrailModel& model);
	~BossColliderGuide();

	void Update();
	void Draw();

private:
	BossColliderEdge *edgeR, *edgeL;
	BossColliderLine *line;
};

class BossColliderLine
{
public:
	BossColliderLine(const D3DXVECTOR3& edgeR, const D3DXVECTOR3& edgeL);
	~BossColliderLine();

	void Draw();

private:
	Transform* transform;
	BoardPolygon *polygon;
};

class BossColliderEdge
{
public:
	BossColliderEdge(const D3DXVECTOR3& pos);
	BossColliderEdge();

	void Update();
	void Draw();

private:
	Transform* transform;
	BoardPolygon *polygon;
};

#endif