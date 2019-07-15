//=====================================
//
//�X�R�A�p�[�e�B�N���R���g���[������[ScoreParticleController.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "ScoreParticleController.h"
#include "ScoreParticle.h"
#include <algorithm>

using namespace std;

/**************************************
�}�N����`
***************************************/
#define SCOREPARTICLE_NUM_MAX		(256)
#define SCOREPARTICLE_EMITTER_MAX	(32)

#define SCOREPARTICLE_SIZE			(&D3DXVECTOR2(10.0f, 10.0f))

#define SCOREPARTICLE_TEX_NAME		("data/TEXTURE/Effect/ScoreParticle.png")
#define SCOREPARTICLE_TEX_DIV		(&D3DXVECTOR2(1.0f, 1.0f))

#define SCOREPARTICLE_LIFEFRAME		(40)
#define SCOREPARTICLE_LIFE_RANGE	(10)
#define SCOREPARTICLE_SPEED_INIT	(2.0f)
#define SCOREPARTICLE_SPEED_RANGE	(2.0f)
#define SCOREPARTICLE_SPEED_TIME	(10.0f)

#define SCOREPARTICLE_DURATION		(5)
#define SCOREPARTICLE_EMIT_NUM		(10)

/**************************************
�\���̒�`
***************************************/
typedef BaseParticleController Base;

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
����������
***************************************/
void ScoreParticleController::Init()
{
	//�e�N�X�`���ǂݍ��݁A�P�ʒ��_�o�b�t�@�쐬
	LoadTexture(SCOREPARTICLE_TEX_NAME);
	MakeUnitBuffer(SCOREPARTICLE_SIZE, SCOREPARTICLE_TEX_DIV);

	//�p�[�e�B�N���R���e�i������
	particleContainer.resize(SCOREPARTICLE_NUM_MAX);
	for (int i = 0; i < SCOREPARTICLE_NUM_MAX; i++)
	{
		particleContainer[i] = new ScoreParticle();
	}

	//�G�~�b�^�R���e�i����
	emitterContainer.resize(SCOREPARTICLE_EMITTER_MAX);
	for (int i = 0; i < SCOREPARTICLE_EMITTER_MAX; i++)
	{
		emitterContainer[i] = new ScoreParticleEmitter();
	}
}

/**************************************
���o����
***************************************/
void ScoreParticleController::Emit()
{

	ForEachEmitter(SCOREPARTICLE_EMIT_NUM, [](BaseEmitter *emitter, BaseParticle *particle)
	{
		particle->transform.pos = emitter->transform.pos;
		particle->Init();
	});
}