//=====================================
//
//�X�R�A�p�[�e�B�N���w�b�_[ScoreParticle.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _SCOREPARTICLE_H_
#define _SCOREPARTICLE_H_

#include "main.h"
#include "Framework\BaseParticle.h"
#include "Framework\BaseEmitter.h"

/**************************************
�}�N����`
***************************************/

/**************************************
ScoreParticle�N���X��`
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
ScoreParticleEmitter�N���X��`
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
�v���g�^�C�v�錾
***************************************/
void InitScoreParticle(int num);
void UninitScoreParticle(int num);
void UpdateScoreParticle(void);
void DrawScoreParticle(void);

void SetScoreParticle(D3DXVECTOR3 pos);

#endif