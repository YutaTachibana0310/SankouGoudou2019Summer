//=====================================
//
//�v���C���[����[player.cpp]
//Author:GP12B332 12 ����
//
//=====================================
#include "player.h"

#include "main.h"
#include "player.h"
#include "PlayerController.h"

#include "star.h"
#include "debugWindow.h"

/**************************************
�}�N����`
***************************************/
#define PLAYER_MODEL  "data/MODEL/airplane000.x"
#define PLAYER_MOVE		(120.0f)

#define TEXTURE_SAMPLE00_SIZE_X	(50) // �e�N�X�`���T�C�Y
#define TEXTURE_SAMPLE00_SIZE_Y	(50) // ����

#define MAX_LENGTH (6)
/**************************************
�\���̒�`
***************************************/


/**************************************
�O���[�o���ϐ�
***************************************/
/**************************************
�v���g�^�C�v�錾
***************************************/


/*************************************
����������
**************************************/
void Player::Init()
{
	meshPlayer = new MeshContainer();
	meshPlayer->Load(PLAYER_MODEL);

	pos = PLAYER_CENTER;
	move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scl = D3DXVECTOR3(2.0f, 2.0f, 2.0f);
	rot = D3DXVECTOR3(0.0f, 59.7f, 0.0f);
	rotDest= D3DXVECTOR3(0.0f, 0.0f, 0.0f);




	return;

}

/***************************************
�I������
****************************************/
void Player::Uninit()
{
	delete meshPlayer;

}
/****************************************
�X�V����
*****************************************/
void Player::Update()
{

	if (SetBomb() == true) {
		DebugText("bomb\n");
	}
}

/*****************************************
�`�揈��
******************************************/
void Player::Draw()
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, quatMatrixs, shadowMatrix, mtxWorld;
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