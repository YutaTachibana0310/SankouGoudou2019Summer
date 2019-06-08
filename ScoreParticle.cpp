//=====================================
//
//�X�R�A�p�[�e�B�N������[ScoreParticle.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "ScoreParticle.h"
#include "Framework\Easing.h"

#include <vector>
#include <array>

using namespace std;

/**************************************
�}�N����`
***************************************/
#define SCOREPARTICLE_SIZE			(10.0f)
#define SCOREPARTICLE_NUM_MAX		(256)

#define SCOREPARTICLE_TEX_NAME		("data/TEXTURE/Effect/ScoreParticle.png")
#define SCOREPARTICLE_TEX_DIV_X		(1)
#define SCOREPARTICLE_TEX_DIV_Y		(1)
#define SCOREPARTICLE_ANIM_TIME		(1)

#define SCOREPARTICLE_LIFEFRAME		(40)
#define SCOREPARTICLE_LIFE_RANGE	(10)
#define SCOREPARTICLE_SPEED_INIT	(2.0f)
#define SCOREPARTICLE_SPEED_RANGE	(2.0f)
#define SCOREPARTICLE_SPEED_TIME	(10.0f)

#define SCOREPARTICLE_DURATION		(5)
#define SCOREPARTICLE_EMIT_NUM		(10)

/**************************************
�X�R�A�p�[�e�B�N���\����
***************************************/
struct ScoreParticle
{
public:
	ScoreParticle()
	{
		transform.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	}

	bool active;

	int cntFrame;
	int lifeFrame;

	Transform transform;

	D3DXVECTOR3 moveDir;
	float speed;

	void Update();
	void GetUV(ParticleUV* pOut);
};

/**************************************
�X�R�A�p�[�e�B�N���G�~�b�^�\����
***************************************/
struct ScoreParticleEmitter
{
	ScoreParticleEmitter(D3DXVECTOR3 *pos)
	{
		active = true;
		cntFrame = 0;
		emitDuration = SCOREPARTICLE_DURATION;
		this->pos = *pos;
	}

	bool active;

	int cntFrame;
	int emitDuration;

	D3DXVECTOR3 pos;

	void Update(array<ScoreParticle, SCOREPARTICLE_NUM_MAX>*);
};

/**************************************
�O���[�o���ϐ�
***************************************/
static LPDIRECT3DVERTEXBUFFER9 unitBuff, worldBuff, uvBuff;
static LPDIRECT3DTEXTURE9 texture;

static array<ScoreParticle, SCOREPARTICLE_NUM_MAX> particleContainer;
static vector<ScoreParticleEmitter> emitterContainer;

/**************************************
�v���g�^�C�v�錾
***************************************/
DWORD EmbedScoreParticleParameter(void);		//���_�o�b�t�@�ւ̃f�[�^�ݒ�

/**************************************
����������
***************************************/
void InitScoreParticle(int num)
{
	//�P�ʒ��_�o�b�t�@�쐬
	MakeParticleUnitBuffer(&D3DXVECTOR2(SCOREPARTICLE_SIZE, SCOREPARTICLE_SIZE),
		&D3DXVECTOR2(SCOREPARTICLE_TEX_DIV_X, SCOREPARTICLE_TEX_DIV_Y),
		&unitBuff);

	//SRT���o�b�t�@�쐬
	MakeTransformBuffer(SCOREPARTICLE_NUM_MAX, &worldBuff);

	//UV���o�b�t�@�쐬
	MakeUVBUffer(SCOREPARTICLE_NUM_MAX, &uvBuff);

	//�e�N�X�`���ǂݍ���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXCreateTextureFromFile(pDevice, SCOREPARTICLE_TEX_NAME, &texture);
}

/**************************************
�I������
***************************************/
void UninitScoreParticle(int num)
{
	SAFE_RELEASE(texture);
	SAFE_RELEASE(unitBuff);
	SAFE_RELEASE(worldBuff);
	SAFE_RELEASE(uvBuff);
}

/**************************************
�X�V����
***************************************/
void UpdateScoreParticle(void)
{
	//�G�~�b�^�[�X�V����
	for (auto itr = emitterContainer.begin(); itr != emitterContainer.end(); itr++)
	{
		if (!itr->active)
			continue;

		itr->Update(&particleContainer);
	}

	//�p�[�e�B�N���X�V����
	for (auto itr = particleContainer.begin(); itr != particleContainer.end(); itr++)
	{
		if (!itr->active)
			continue;

		itr->Update();
	}
}

/**************************************
�`�揈��
***************************************/
void DrawScoreParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�o�b�t�@�Ƀf�[�^��ݒ�
	DWORD particleCount = EmbedScoreParticleParameter();

	//�X�g���[���\�[�X���g���ݒ�
	pDevice->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | particleCount);
	pDevice->SetStreamSourceFreq(1, D3DSTREAMSOURCE_INSTANCEDATA | 1);
	pDevice->SetStreamSourceFreq(2, D3DSTREAMSOURCE_INSTANCEDATA | 1);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, texture);

	//�X�g���[���\�[�X�ݒ�
	pDevice->SetStreamSource(0, unitBuff, 0, sizeof(ParticleUnit));
	pDevice->SetStreamSource(1, worldBuff, 0, sizeof(Transform));
	pDevice->SetStreamSource(2, uvBuff, 0, sizeof(ParticleUV));

	//�`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NUM_VERTEX, 0, NUM_POLYGON);

	//�X�g���[���\�[�X���g������
	pDevice->SetStreamSourceFreq(0, 1);
	pDevice->SetStreamSourceFreq(1, 1);
	pDevice->SetStreamSourceFreq(2, 1);
}

/**************************************
���_�o�b�t�@�ւ̃f�[�^�ݒ�
***************************************/
DWORD EmbedScoreParticleParameter(void)
{
	DWORD particleCount = 0;

	//���_�o�b�t�@�����b�N
	Transform *pTransform;
	worldBuff->Lock(0, 0, (void**)&pTransform, 0);
	ParticleUV *pUV;
	uvBuff->Lock(0, 0, (void**)&pUV, 0);

	//���_�o�b�t�@�Ƀf�[�^��ݒ�
	for (auto itr = particleContainer.begin(); itr != particleContainer.end(); itr++)
	{
		if (!itr->active)
			continue;

		*pTransform = itr->transform;
		itr->GetUV(pUV);

		pTransform++;
		pUV++;

		particleCount ++;
	}

	//���_�o�b�t�@���A�����b�N
	worldBuff->Unlock();
	uvBuff->Unlock();

	return particleCount;
}

/**************************************
�p�[�e�B�N���X�V����
***************************************/
void ScoreParticle::Update()
{
	const float EndSpeed = 0.2f;
	const float InitScale = 1.0f, EndScale = 0.0f;

	//�ړ�����
	float tSpeed = (float)cntFrame / (float)SCOREPARTICLE_SPEED_TIME;
	float currentSpeed = Easing<float>::GetEasingValue(tSpeed, &speed, &EndSpeed, EasingType::InExponential);
	transform.pos += moveDir * currentSpeed;

	//�X�P�[������
	float tScale = (float)cntFrame / (float)lifeFrame;
	float currentScale = Easing<float>::GetEasingValue(tScale, &InitScale, &EndScale, EasingType::OutExponential);
	transform.scale = D3DXVECTOR3(currentScale, currentScale, currentScale);

	//��������
	cntFrame++;
	if (cntFrame > lifeFrame)
	{
		active = false;
	}
}

/**************************************
UV���W���菈��
***************************************/
void ScoreParticle::GetUV(ParticleUV* pOut)
{
	static float sizeX = 1.0f / SCOREPARTICLE_TEX_DIV_X;

	static float sizeY = 1.0f / SCOREPARTICLE_TEX_DIV_Y;

	int x = cntFrame % SCOREPARTICLE_TEX_DIV_X;
	int y = cntFrame / SCOREPARTICLE_TEX_DIV_X;
	pOut->u = sizeX * x;
	pOut->v = sizeY * y;
}

/**************************************
�G�~�b�^�[�X�V����
***************************************/
void ScoreParticleEmitter::Update(array<ScoreParticle, SCOREPARTICLE_NUM_MAX>* container)
{
	//���o����
	for (int i = 0; i < SCOREPARTICLE_EMIT_NUM; i++)
	{
		for (auto itr = container->begin(); itr != container->end(); itr++)
		{
			if (itr->active)
				continue;

			itr->moveDir.x = RandomRangef(-1.0f, 1.0f);
			itr->moveDir.y = RandomRangef(-1.0f, 1.0f);
			itr->moveDir.z = RandomRangef(-1.0f, 1.0f);

			itr->lifeFrame = SCOREPARTICLE_LIFEFRAME + RandomRange(-SCOREPARTICLE_LIFE_RANGE, SCOREPARTICLE_LIFE_RANGE);
			itr->cntFrame = 0;

			itr->speed = SCOREPARTICLE_SPEED_INIT + RandomRangef(-SCOREPARTICLE_SPEED_RANGE, SCOREPARTICLE_SPEED_RANGE);
			itr->transform.pos = pos;

			itr->active = true;
			break;
		}
	}

	//��������
	cntFrame++;
	if (cntFrame > emitDuration)
	{
		active = false;
	}
}

/**************************************
�X�R�A�p�[�e�B�N����������
***************************************/
void SetScoreParticle(D3DXVECTOR3 pos)
{
	//���g�p�̃G�~�b�^�[������
	for (auto itr = emitterContainer.begin(); itr != emitterContainer.end(); itr++)
	{
		if (itr->active)
			continue;

		itr->pos = pos;
		itr->cntFrame = 0;
		itr->active = true;
		return;
	}

	//�V���ɃG�~�b�^�[���쐬���ăR���e�i�ɒǉ�
	emitterContainer.push_back(ScoreParticleEmitter(&pos));
}