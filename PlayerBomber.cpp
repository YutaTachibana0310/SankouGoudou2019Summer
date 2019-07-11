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

	transform.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	transform.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	transform.rot = D3DXVECTOR3(0.0f, D3DXToRadian(180.0f), 0.0f);

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
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, quatMatrixs, mtxWorld, view, invView;
	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, transform.scale.y, transform.scale.x, transform.scale.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, transform.rot.y, transform.rot.x, transform.rot.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	//�t�s����|����
	view = GetMtxView();
	D3DXMatrixInverse(&view, NULL, &invView);
	invView._41 = 0.0f;
	invView._42 = 0.0f;
	invView._43 = 0.0f;
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &invView);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, transform.pos.x, transform.pos.y, transform.pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

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
void PlayerBomber::Set(D3DXVECTOR3 *pos, D3DXVECTOR3 initpos)
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

	float time = cntFrame;

	D3DXVECTOR3 diff = *targetPos - transform.pos;

	D3DXVECTOR3 acceleration = (diff - velocity * time) * 2.0f / (time * time);

	velocity += acceleration;

	cntFrame--;
}
