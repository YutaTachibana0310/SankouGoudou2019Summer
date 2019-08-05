//=====================================
//
//�{������[PlayerBomber.cpp]
//Author:GP12B332 12 ����
//
//=====================================
#include "PlayerBomber.h"
#include "camera.h"

/**************************************
�}�N����`
***************************************/
#define PLAYERBOMBER_TEXTURE_NAME	"data/MODEL/airplane000.x"

#define BOMBER_X		(30)
#define BOMBER_Y		(30)
#define BOMBER_Z		(30)

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
void PlayerBomber::Init(void)
{
	active = true;
	cntFrame = 0;
	reachFrame = 0;

	velocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

}
/**************************************
�I������
***************************************/
void PlayerBomber::Uninit(void)
{
	active = false;
	

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

}


/**************************************
�f�X�g���N�^
***************************************/
PlayerBomber::~PlayerBomber()
{
	

	instanceCount--;
	if (instanceCount == 0)
	{
		//�C���X�^���X���c���Ă��Ȃ���΃e�N�X�`�����

	}
}

/**************************************
�z�[�~���O�Ώۂ̃A�h���X���擾
����(�z�[�~���O�Ώۂ̃A�h���X�A�{���̃Z�b�g�ʒu)
***************************************/
void PlayerBomber::Set(D3DXVECTOR3 pos, D3DXVECTOR3 initpos)
{
	//active = true;
	Init();
	transform.pos = initpos;
	targetPos = pos;
	cntFrame = reachFrame = 120;
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
