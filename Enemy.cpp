//=====================================
//
//�G�̏��� [Enemy.cpp]
//
//Author:�n�@�O��
//=====================================
#include "Enemy.h"


/**************************************
�}�N����`
***************************************/
//#define ENEMY_NUM (4) //1�O���[�v�̃L���[�u(�G�l�~�[)�̗�
#define ENEMY_MODEL  "data/MODEL/airplane000.x"



//Enemy
/****************************************
�R���X�g���N�^
****************************************/
//Enemy::Enemy()
//{
//
//}

/****************************************
�f�X�g���N�^
****************************************/
//Enemy::~Enemy()
//{
//
//}

//EnemyStraight
/****************************************
�R���X�g���N�^
****************************************/
EnemyStraight::EnemyStraight()
{
	//�������̃R�[�h�̓R���X�g���N�^�ɓ����H
}

/****************************************
�f�X�g���N�^
****************************************/
EnemyStraight::~EnemyStraight()
{
	//�I�������̃R�[�h�̓f�X�g���N�^�ɓ����H
}

/****************************************
����������
****************************************/
HRESULT  EnemyStraight::Init(void)
{
	bUse = false;
	meshPlayer = new MeshContainer();
	meshPlayer->Load(ENEMY_MODEL);

	pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scl = D3DXVECTOR3(2.0f, 2.0f, 2.0f);
	rot = D3DXVECTOR3(0.0f, 59.7f, 0.0f);
	rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	cntFrame = 0;
	return S_OK;
}
/****************************************
�I������
*****************************************/
void EnemyStraight::Uninit(void)
{
	//SAFE_RELEASE?
	SAFE_DELETE(meshPlayer);
}
/****************************************
�X�V����
*****************************************/
void EnemyStraight::Update(void)
{
	if (bUse)	
	{
		move.z = -1.0f;
		pos += move;
		//count����
		cntFrame++;
	}

}

/****************************************
�`�揈��
*****************************************/
void EnemyStraight::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;
	
	if (bUse)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&mtxWorld);

		// �X�P�[���𔽉f
		D3DXMatrixScaling(&mtxScl, scl.y, scl.x, scl.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);

		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTranslate, pos.x, pos.y, pos.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

		meshPlayer->Draw();
	}
				
}
/****************************************
�Z�b�g����
*****************************************/
void EnemyStraight::Set(D3DXVECTOR3 pos)
{
		//if (!bUse)
		//{
			this->pos = pos;
			bUse = true;
			//pos.x += 10.0f;

		//}
}




//EnemyChange
/****************************************
�R���X�g���N�^
****************************************/
EnemyChange::EnemyChange()
{

}
/****************************************
�f�X�g���N�^
****************************************/
EnemyChange::~EnemyChange()
{

}
/****************************************
����������
****************************************/
HRESULT EnemyChange::Init(void)
{
	bUse = false;
	meshPlayer = new MeshContainer();
	meshPlayer->Load(ENEMY_MODEL);

	pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scl = D3DXVECTOR3(2.0f, 2.0f, 2.0f);
	rot = D3DXVECTOR3(0.0f, 59.7f, 0.0f);
	rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	cntFrame = 0;
	
	return S_OK;
}
/****************************************
�I������
*****************************************/
void EnemyChange::Uninit()
{
	//SAFE_RELEASE?
	SAFE_DELETE(meshPlayer);
}
/****************************************
�X�V����
*****************************************/
void EnemyChange::Update()
{
	if (bUse)
	{
		if (cntFrame > 80 && cntFrame < 150)
		{
			move.z = 0.0f;
		}
		else if (cntFrame >= 150)
		{
			move.z = -1.0f;
		}
		else
		{
			move.z = 1.0f;
		}
		pos += move;
		//count����
		cntFrame++;
	}
	
}
/****************************************
�`�揈��
*****************************************/
void EnemyChange::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;

	if (bUse)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&mtxWorld);

		// �X�P�[���𔽉f
		D3DXMatrixScaling(&mtxScl, scl.y, scl.x, scl.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);

		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTranslate, pos.x, pos.y, pos.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

		meshPlayer->Draw();
	}
}

/****************************************
�Z�b�g����
*****************************************/
void EnemyChange::Set(D3DXVECTOR3 pos)
{
	this->pos = pos;
	bUse = true;
	
}