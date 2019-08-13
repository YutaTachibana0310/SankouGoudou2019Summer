//=====================================
//
//�{������[PlayerBomber.cpp]
//Author:GP12B332 12 ����
//
//=====================================
#include "PlayerBomber.h"
#include "camera.h"
#include "GameParticleManager.h"

/**************************************
�}�N����`
***************************************/
#define			BOMBER_MOVE			(10.0f)
#define			BOMBER_REACH_FRAME	(60)
#define			BOBMER_INIT_SPEED	(5.0f)

/**************************************
�\���̒�`
***************************************/

/**************************************
static�����o
***************************************/
int PlayerBomber::instanceCount = 0;				//�C���X�^���X�J�E���^

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
����������
***************************************/
void PlayerBomber::Init(const D3DXVECTOR3& moveDir)
{
	active = true;
	cntFrame = 0;
	reachFrame = 0;

	transform.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	transform.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	velocity = moveDir * BOBMER_INIT_SPEED;

	GameParticleManager::Instance()->SetPlayerBomberParticle(&transform.pos, &active);

	collider->active = true;
}

/**************************************
�I������
***************************************/
void PlayerBomber::Uninit(void)
{
	active = false;
	collider->active = false;
}

/**************************************
�X�V����
***************************************/
void PlayerBomber::Update(void)
{
	if (!active)
		return;
	
	CalcBomber();
	transform.pos += velocity;
	
	if (cntFrame == 0)
		Uninit();

}

/**************************************
�`�揈��
***************************************/
void PlayerBomber::Draw(void)
{
	if (!active)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	transform.SetWorld();

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

/**************************************
�R���X�g���N�^
***************************************/
PlayerBomber::PlayerBomber()
{
	active = false;
	instanceCount++;

	collider = new BoxCollider3D(BoxCollider3DTag::PlayerBomber, &transform.pos);
	collider->AddObserver(this);
	collider->active = false;
}

/**************************************
�f�X�g���N�^
***************************************/
PlayerBomber::~PlayerBomber()
{
	instanceCount--;
}

/**************************************
�z�[�~���O�Ώۂ̃A�h���X���擾
����(�z�[�~���O�Ώۂ̃A�h���X�A�{���̃Z�b�g�ʒu)
***************************************/
void PlayerBomber::Set(D3DXVECTOR3 pos, D3DXVECTOR3 initpos)
{
	transform.pos = initpos;
	targetPos = pos;
	cntFrame = reachFrame = BOMBER_REACH_FRAME;
}

/***************************************
�����x�̌v�Z����
****************************************/
void PlayerBomber::CalcBomber(void)
{
	if (cntFrame <= 0)
	{
		return;
	}

	float time = (float)cntFrame;

	D3DXVECTOR3 diff = targetPos - transform.pos;

	D3DXVECTOR3 acceleration = (diff - velocity * time) * 2.0f / (time * time);

	velocity += acceleration;

	cntFrame--;
}

/***************************************
�Փ˒ʒm����
****************************************/
void PlayerBomber::OnNotified(BoxCollider3DTag other)
{
	Uninit();
}