//=====================================
//
//�v���C���[�o���b�g�p�[�e�B�N������[PlayerBulletParticle.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "PlayerBulletParticle.h"
#include "Framework\Easing.h"

#include <vector>
#include <array>

using namespace std;

/**************************************
�}�N����`
***************************************/
#define PLAYERBULLETPARTICLE_TEXTURE_NAME	"data/TEXTURE/Effect/PlayerBulletParticle.png"
#define PLAYERBULLETPARTCILE_NUM_MAX		(4096)
#define PLAYERBULLETPARTICLE_SIZE			(2.0f)

#define PLAYERBULLETPARTICLE_LIFEFRAME		(10)
#define PLAYERBULLETPARTTCLE_LIFE_RANGE		(3)

/**************************************
�v���C���[�o���b�g�p�[�e�B�N���\����
***************************************/
struct PlayerBulletParticle
{
	bool active;
	int cntFrame;
	int lifeFrame;
	Transform transform;
	D3DXVECTOR3 moveDir;
	float speed;

	void Update();
};

/**************************************
�v���C���[�o���b�g�p�[�e�B�N���G�~�b�^�\����
***************************************/
struct PlayerBulletParticleEmitter
{
	PlayerBulletParticleEmitter(D3DXVECTOR3 *pPos, bool *pActive, const D3DXVECTOR3 *edgeRight, const D3DXVECTOR3 *edgeLeft)
	{
		parentActive = pActive;
		parentPos = pPos;
		this->edgeLeft = *edgeLeft;
		this->edgeRight = *edgeRight;
		active = true;
	}

	bool active;
	bool *parentActive;						//�e�̃A�N�e�B�u�|�C���^
	D3DXVECTOR3 *parentPos;					//�e�̍��W�|�C���^
	D3DXVECTOR3 edgeRight, edgeLeft;		//�p�[�e�B�N�������̒[�_

	void Update(array<PlayerBulletParticle, PLAYERBULLETPARTCILE_NUM_MAX>*);
};

/**************************************
�O���[�o���ϐ�
***************************************/
static LPDIRECT3DVERTEXBUFFER9 unitBuff, transformBuffer, uvBuffer;
static LPDIRECT3DTEXTURE9 texture;

static array<PlayerBulletParticle, PLAYERBULLETPARTCILE_NUM_MAX> particleContainer;
static vector<PlayerBulletParticleEmitter> emitterContainer;

/**************************************
�v���g�^�C�v�錾
***************************************/
DWORD EmbedPlayerBulletParticleParameter(void);		//���_�o�b�t�@�ւ̃f�[�^�ݒ�

/**************************************
����������
***************************************/
void InitPlayerBulletParticle(int num)
{
	//�P�ʒ��_�o�b�t�@�쐬
	MakeParticleUnitBuffer(&D3DXVECTOR2(PLAYERBULLETPARTICLE_SIZE, PLAYERBULLETPARTICLE_SIZE),
		&D3DXVECTOR2(1.0f, 1.0f),
		&unitBuff);

	//SRT���o�b�t�@�쐬
	MakeTransformBuffer(PLAYERBULLETPARTCILE_NUM_MAX, &transformBuffer);

	//UV���o�b�t�@�쐬
	MakeTransformBuffer(PLAYERBULLETPARTCILE_NUM_MAX, &uvBuffer);

	//�e�N�X�`���ǂݍ���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXCreateTextureFromFile(pDevice, PLAYERBULLETPARTICLE_TEXTURE_NAME, &texture);
}

/**************************************
�I������
***************************************/
void UninitPlayerBulletParticle(int num)
{
	SAFE_RELEASE(texture);
	SAFE_RELEASE(unitBuff);
	SAFE_RELEASE(transformBuffer);
	SAFE_RELEASE(uvBuffer);
}

/**************************************
�X�V����
***************************************/
void UpdatePlayerBulletParticle(void)
{
	for (auto itr = emitterContainer.begin(); itr != emitterContainer.end(); itr++)
	{
		if (!itr->active)
			continue;

		itr->Update(&particleContainer);
	}

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
void DrawPlayerBulletParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���Z����
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//���_�o�b�t�@�Ƀf�[�^��ݒ�
	DWORD particleCount = EmbedPlayerBulletParticleParameter();

	//�X�g���[���\�[�X���g���ݒ�
	pDevice->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | particleCount);
	pDevice->SetStreamSourceFreq(1, D3DSTREAMSOURCE_INSTANCEDATA | 1);
	pDevice->SetStreamSourceFreq(2, D3DSTREAMSOURCE_INSTANCEDATA | 1);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, texture);

	//�X�g���[���\�[�X�ݒ�
	pDevice->SetStreamSource(0, unitBuff, 0, sizeof(ParticleUnit));
	pDevice->SetStreamSource(1, transformBuffer, 0, sizeof(Transform));
	pDevice->SetStreamSource(2, uvBuffer, 0, sizeof(ParticleUV));

	//�`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NUM_VERTEX, 0, NUM_POLYGON);

	//�X�g���[���\�[�X���g���ݒ�
	pDevice->SetStreamSourceFreq(0, 1);
	pDevice->SetStreamSourceFreq(1, 1);
	pDevice->SetStreamSourceFreq(2, 1);

	//�ʏ�`��ɕ��A
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

/**************************************
���_�o�b�t�@�ւ̃f�[�^�ݒ�
***************************************/
DWORD EmbedPlayerBulletParticleParameter(void)
{
	DWORD particleCount = 0;

	//���_�o�b�t�@�����b�N
	Transform *pTransform;
	transformBuffer->Lock(0, 0, (void**)&pTransform, 0);

	//���_�o�b�t�@�Ƀf�[�^��ݒ�
	for (auto itr = particleContainer.begin(); itr != particleContainer.end(); itr++)
	{
		if (!itr->active)
			continue;

		*pTransform = itr->transform;

		pTransform++;
		particleCount++;
	}

	//���_�o�b�t�@���A�����b�N
	transformBuffer->Unlock();

	return particleCount;
}

/**************************************
�p�[�e�B�N���X�V����
***************************************/
void PlayerBulletParticle::Update()
{
	//�ړ�����
	transform.pos += moveDir * speed;

	//��������
	cntFrame++;
	if (cntFrame > lifeFrame)
	{
		active = false;
	}
}

/**************************************
�G�~�b�^�[�X�V����
***************************************/
void PlayerBulletParticleEmitter::Update(array<PlayerBulletParticle, PLAYERBULLETPARTCILE_NUM_MAX>* container)
{
	const int EmitNum = 50;
	const float Speed = 2.0f;

	//���o����
	int countEmit = 0;
	for (auto itr = container->begin(); itr != container->end(); itr++)
	{
		if (itr->active)
			continue;

		itr->moveDir.x = RandomRangef(-1.0f, 1.0f);
		itr->moveDir.y = RandomRangef(-1.0f, 1.0f);
		itr->moveDir.z = -2.0f;
		D3DXVec3Normalize(&itr->moveDir, &itr->moveDir);

		itr->lifeFrame = PLAYERBULLETPARTICLE_LIFEFRAME + RandomRange(-PLAYERBULLETPARTTCLE_LIFE_RANGE, PLAYERBULLETPARTTCLE_LIFE_RANGE);
		itr->cntFrame = 0;

		itr->speed = Speed;

		float t = RandomRangef(0.0f, 1.0f);
		itr->transform.pos = Easing<D3DXVECTOR3>::GetEasingValue(t, &edgeLeft, &edgeRight, EasingType::Linear);
		itr->transform.pos.z = parentPos->z;

		itr->transform.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		itr->transform.scale.x += fabsf(itr->moveDir.x)* 10.0f;
		itr->transform.scale.y += fabsf(itr->moveDir.y)* 10.0f;

		itr->active = true;

		countEmit++;
		if(countEmit == EmitNum)
			break;
	}


	//��������
	if (!*parentActive)
	{
		active = false;
	}
}

/**************************************
�v���C���[�o���b�g��������
***************************************/
void SetPlayerBulletParticle(D3DXVECTOR3 *pPos, bool *pActive, const D3DXVECTOR3 *edgeRight, const D3DXVECTOR3 *edgeLeft)
{
	//���g�p�̃G�~�b�^�[�̒�����Z�b�g
	for (auto itr = emitterContainer.begin(); itr != emitterContainer.end(); itr++)
	{
		if (itr->active)
			continue;

		itr->active = true;
		itr->parentActive = pActive;
		itr->parentPos = pPos;
		itr->edgeLeft = *edgeLeft;
		itr->edgeRight = *edgeRight;
		return;
	}

	//�V���ɃG�~�b�^�[���쐬���ăR���e�i�ɒǉ�
	emitterContainer.push_back(PlayerBulletParticleEmitter(pPos, pActive, edgeRight, edgeLeft));
}