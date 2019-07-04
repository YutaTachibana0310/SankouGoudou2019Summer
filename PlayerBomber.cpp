//=====================================
//
//�{������[PlayerBomber.cpp]
//Author:GP12B332 12 ����
//
//=====================================
#include "PlayerBomber.h"


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
LPDIRECT3DTEXTURE9 PlayerBomber::texture = NULL;	//�e�N�X�`��

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
	transform.pos += velocity /60.0f;
	
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

	//LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//VERTEX_3D* p;

	////vtxBuff->Lock(0, 0, (void**)&p, 0);
	////vtxBuff->Unlock();

	//pDevice->SetFVF(FVF_VERTEX_3D);

	//pDevice->SetTexture(0, texture);

	//pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(VERTEX_3D));

	//D3DXMATRIX mtxWorld;
	//D3DXMatrixIdentity(&mtxWorld);
	//D3DXMatrixTranslation(&mtxWorld, transform.pos.x, transform.pos.y, transform.pos.z);

	//pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, quatMatrixs, shadowMatrix, mtxWorld;
	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, transform.scale.y, transform.scale.x, transform.scale.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, transform.rot.y, transform.rot.x, transform.rot.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, transform.pos.x, transform.pos.y, transform.pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	mesh->Draw();

}

/**************************************
�R���X�g���N�^
***************************************/
PlayerBomber::PlayerBomber()
{
	active = false;
	instanceCount++;
	mesh = new MeshContainer();

	mesh->Load(PLAYERBOMBER_TEXTURE_NAME);

}


/**************************************
�f�X�g���N�^
***************************************/
PlayerBomber::~PlayerBomber()
{
	
	SAFE_RELEASE(vtxBuff);
	SAFE_DELETE(mesh);

	instanceCount--;
	if (instanceCount == 0)
	{
		//�C���X�^���X���c���Ă��Ȃ���΃e�N�X�`�����
		SAFE_RELEASE(texture);

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

	float time = cntFrame/60.0f;

	D3DXVECTOR3 diff = *targetPos - transform.pos;

	D3DXVECTOR3 acceleration = (diff - velocity * time) * 2.0f / (time * time);

	velocity += acceleration/60.0f;

	cntFrame--;
}