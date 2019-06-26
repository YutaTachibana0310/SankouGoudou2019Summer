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

#include "starUI.h"
#include "debugWindow.h"

/**************************************
�}�N����`
***************************************/
#define PLAYER_MODEL  "data/MODEL/airplane000.x"

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
	scl = D3DXVECTOR3(2.0f, 2.0f, 2.0f);
	rot = D3DXVECTOR3(0.0f, 59.7f, 0.0f);

	trail = new PlayerTrail();

	return;
}

/***************************************
�I������
****************************************/
void Player::Uninit()
{
	delete meshPlayer;
	delete trail;

}
/****************************************
�X�V����
*****************************************/
void Player::Update()
{

	if (SetBomb() == true) {
		DebugText("bomb\n");
	}

	trail->Update();
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
	trail->Draw();

}