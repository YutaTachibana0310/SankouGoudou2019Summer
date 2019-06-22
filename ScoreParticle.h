//=====================================
//
//スコアパーティクルヘッダ[ScoreParticle.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _SCOREPARTICLE_H_
#define _SCOREPARTICLE_H_

#include "main.h"
#include "Framework\BaseParticle.h"
#include "Framework\BaseEmitter.h"

/**************************************
マクロ定義
***************************************/

/**************************************
ScoreParticleクラス定義
***************************************/
class ScoreParticle : public BaseParticle
{
public:
	ScoreParticle() {};
	~ScoreParticle() {};

	void Init();
	void Uninit();
	void Update();
	
	D3DXVECTOR3 moveDir;
	float speed;
};

/**************************************
ScoreParticleEmitterクラス定義
***************************************/
class ScoreParticleEmitter : public BaseEmitter
{
public:
	ScoreParticleEmitter(D3DXVECTOR3 *pos);
	ScoreParticleEmitter() : BaseEmitter() {};

	void Init();
	void Uninit();
	void Update();
};

/**************************************
プロトタイプ宣言
***************************************/
void InitScoreParticle(int num);
void UninitScoreParticle(int num);
void UpdateScoreParticle(void);
void DrawScoreParticle(void);

void SetScoreParticle(D3DXVECTOR3 pos);

#endif