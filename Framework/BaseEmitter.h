//=====================================
//
//ベースエミッタヘッダ[BaseEmitter.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BASEEMITTER_H_
#define _BASEEMITTER_H_

#include "../main.h"
#include <vector>
#include <memory>

/**************************************
前方宣言
***************************************/
class BaseParticle;

/**************************************
BaseEmitterクラス
※継承先でInit(), Uninit(), Update()を実装する
***************************************/
class BaseEmitter
{
public:
	BaseEmitter(D3DXVECTOR3 *pos);
	BaseEmitter();
	virtual ~BaseEmitter();

	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	bool active;

	Transform transform;

protected:
	int cntFrame;
	int duration;
};

#endif