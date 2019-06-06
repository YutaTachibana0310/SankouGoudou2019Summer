//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : �n糗Ǒ�
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "PlayerController.h"

#include "star.h"
#include "debugWindow.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

PLAYER player;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayer(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	player.posPlayer = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);
	player.rotPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	player.nCountAnim = 0;
	player.nPatternAnim = 0;

	//�ړ���̐��̈ʒu���擾�i���������͐��̔z�u���Ȃ��̂Ōʎw��j
	GetStarPosition(player.targetpos);
	player.targetpos[CENTER] = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);

	// ���_���̍쐬
	MakeVertexPlayer();

	//���@2D�摜�Ȃ̂�3D���f���ɕύX���K�v�A2D�͍ŏI�I�ɏ�������
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile( pDevice,		// �f�o�C�X�̃|�C���^
		TEXTURE_GAME_SAMPLE00,				// �t�@�C���̖��O
		&player.D3DTexturePlayer );			// �ǂݍ��ރ������̃|�C���^

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{
	if(player.D3DTexturePlayer != NULL )	//
	{	// �e�N�X�`���̊J��
		player.D3DTexturePlayer->Release();
		player.D3DTexturePlayer = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{

	//�ړ���̎w��
	SetPlayerTargetPosition(&player.goal);

	//�ړ������i���ڈړ��Ȃ̂ŕύX���K�v�S�������낵���j
	player.posPlayer = player.targetpos[player.goal];

	SetVertex();

	if (SetBomb() == true) {
		DebugText("bomb\n");
	}

}



//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture( 0, player.D3DTexturePlayer );

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, player.vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���W�̐ݒ�
	player.vertexWk[0].vtx = D3DXVECTOR3(player.posPlayer.x, player.posPlayer.y, player.posPlayer.z);
	player.vertexWk[1].vtx = D3DXVECTOR3(player.posPlayer.x + TEXTURE_SAMPLE00_SIZE_X, player.posPlayer.y, player.posPlayer.z);
	player.vertexWk[2].vtx = D3DXVECTOR3(player.posPlayer.x, player.posPlayer.y +TEXTURE_SAMPLE00_SIZE_Y, player.posPlayer.z);
	player.vertexWk[3].vtx = D3DXVECTOR3(player.posPlayer.x + TEXTURE_SAMPLE00_SIZE_X, player.posPlayer.y + TEXTURE_SAMPLE00_SIZE_Y, player.posPlayer.z);

	// rhw�̐ݒ�
	player.vertexWk[0].rhw =
	player.vertexWk[1].rhw =
	player.vertexWk[2].rhw =
	player.vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	player.vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	player.vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	player.vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	player.vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	player.vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	player.vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	player.vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	player.vertexWk[3].tex = D3DXVECTOR2(0.2f, 1.0f);

	

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetVertex(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���W�̐ݒ�
	player.vertexWk[0].vtx = D3DXVECTOR3(player.posPlayer.x, player.posPlayer.y, player.posPlayer.z);
	player.vertexWk[1].vtx = D3DXVECTOR3(player.posPlayer.x + TEXTURE_SAMPLE00_SIZE_X, player.posPlayer.y, player.posPlayer.z);
	player.vertexWk[2].vtx = D3DXVECTOR3(player.posPlayer.x, player.posPlayer.y + TEXTURE_SAMPLE00_SIZE_Y, player.posPlayer.z);
	player.vertexWk[3].vtx = D3DXVECTOR3(player.posPlayer.x + TEXTURE_SAMPLE00_SIZE_X, player.posPlayer.y + TEXTURE_SAMPLE00_SIZE_Y, player.posPlayer.z);
}
