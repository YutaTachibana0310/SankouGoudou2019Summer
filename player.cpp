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

	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rotDest= D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	/***************************************
	�n�ӂ��񑤂̏���
	****************************************/
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	posPlayer = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);

	//�ړ���̐��̈ʒu���擾�i���������͐��̔z�u���Ȃ��̂Ōʎw��j
	GetStarPosition(targetpos);
	targetpos[CENTER] = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);

	// ���_���̍쐬
	MakeVertexPlayer();

	return;

}

/***************************************
�I������
****************************************/
void Player::Uninit()
{
	delete meshPlayer;

	/*************************************
	�n�ӂ��񑤂̏���
	**************************************/
	if (D3DTexturePlayer != NULL)	//
	{	// �e�N�X�`���̊J��
		D3DTexturePlayer->Release();
		D3DTexturePlayer = NULL;
	}
}
/****************************************
�X�V����
*****************************************/
void Player::Update()
{
	/******************************
	�n糂����̏���
	********************************/
	//�ړ���̎w��
	SetPlayerTargetPosition(&goal);

	//�ړ������i���ڈړ��Ȃ̂ŕύX���K�v�S�������낵���j
	posPlayer = targetpos[goal];

	SetVertex();

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
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, quatMatrixs, shadowMatrix,mtxWorld;
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

	/***************************************
	�n糂��񑤂̏���
	****************************************/
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, D3DTexturePlayer);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT Player::MakeVertexPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���W�̐ݒ�
	vertexWk[0].vtx = D3DXVECTOR3(posPlayer.x, posPlayer.y, posPlayer.z);
	vertexWk[1].vtx = D3DXVECTOR3(posPlayer.x + TEXTURE_SAMPLE00_SIZE_X, posPlayer.y, posPlayer.z);
	vertexWk[2].vtx = D3DXVECTOR3(posPlayer.x, posPlayer.y + TEXTURE_SAMPLE00_SIZE_Y, posPlayer.z);
	vertexWk[3].vtx = D3DXVECTOR3(posPlayer.x + TEXTURE_SAMPLE00_SIZE_X, posPlayer.y + TEXTURE_SAMPLE00_SIZE_Y, posPlayer.z);

	// rhw�̐ݒ�
	vertexWk[0].rhw =
		vertexWk[1].rhw =
		vertexWk[2].rhw =
		vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexWk[3].tex = D3DXVECTOR2(0.2f, 1.0f);



	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void Player::SetVertex(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���W�̐ݒ�
	vertexWk[0].vtx = D3DXVECTOR3(posPlayer.x, posPlayer.y, posPlayer.z);
	vertexWk[1].vtx = D3DXVECTOR3(posPlayer.x + TEXTURE_SAMPLE00_SIZE_X, posPlayer.y, posPlayer.z);
	vertexWk[2].vtx = D3DXVECTOR3(posPlayer.x, posPlayer.y + TEXTURE_SAMPLE00_SIZE_Y, posPlayer.z);
	vertexWk[3].vtx = D3DXVECTOR3(posPlayer.x + TEXTURE_SAMPLE00_SIZE_X, posPlayer.y + TEXTURE_SAMPLE00_SIZE_Y, posPlayer.z);
}

