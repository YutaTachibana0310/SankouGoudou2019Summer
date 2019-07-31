//=====================================
//
//エネミーガイドアローヘッダ[EnemyGuideArrow.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _ENEMYGUIDEARROW_H_
#define _ENEMYGUIDEARROW_H_

#include "main.h"
#include "Framework\BaseParticle.h"
#include "Framework\BaseEmitter.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class EnemyGuideArrow : public BaseParticle
{
public:
	void Init();
	void Update();
};

class EnemyGuideArrowEmitter : public BaseEmitter
{
public:
	void Init();
	void Update();

	D3DXVECTOR3 start, end;
};

#endif