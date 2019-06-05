//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : �n糗Ǒ�
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "player_controller.h"
#include "UIdrawer.h"
#include "star.h"

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
PLAYER_CONTROLLER* pplayer_c;
OBJECT*	pstar;

LPD3DXFONT				g_pD3DXFont = NULL;			// �t�H���g�ւ̃|�C���^

//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayer(void)
{
	pstar = GetStar();
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	player.g_posPlayer = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);
	player.g_rotPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	player.g_nCountAnim = 0;
	player.g_nPatternAnim = 0;

	player.move_wait = true;

	
	for (int i = 0; i < STAR_MAX; i++,pstar++) {
		player.targetpos[i] = pstar->position;
	}
	player.targetpos[CENTER] = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);

	// ���_���̍쐬
	MakeVertexPlayer();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile( pDevice,		// �f�o�C�X�̃|�C���^
		TEXTURE_GAME_SAMPLE00,				// �t�@�C���̖��O
		&player.g_pD3DTexturePlayer );			// �ǂݍ��ރ������̃|�C���^

		// �����_�����O�X�e�[�g�p�����[�^�̐ݒ�
	// ���\���p�t�H���g��ݒ�
	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Terminal"), &g_pD3DXFont);


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{
	if(player.g_pD3DTexturePlayer != NULL )	//
	{	// �e�N�X�`���̊J��
		player.g_pD3DTexturePlayer->Release();
		player.g_pD3DTexturePlayer = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{
	

	pplayer_c = GetPlayerController();

	// �A�j���[�V����

	//�^�C�}�[�X�V
	player.g_nCountAnim++;
	//TIME_ANIMATION = 100
	if ((player.g_nCountAnim % TIME_ANIMATION) == 1){
		//�p�^�[���̐؂�ւ�,ANIM_PATTERN_NUM=�p�^�[����
		player.g_nPatternAnim = (player.g_nPatternAnim + 1) % ANIM_PATTERN_NUM;
		//�p�^�[��No��n���ăe�N�X�`�����W�X�V
		SetTexturePlayer(player.g_nPatternAnim);
	}

	//�x�N�g��
	D3DXVECTOR3 BtoPvec[MAX_LENGTH];
	//���K��
	D3DXVECTOR3 norBtoP;
	//����
	FLOAT BtoPLen;

	SetPlayerTargetPosition(&player.goal);
	
	player.g_posPlayer = player.targetpos[player.goal];

	////�ړ�����
	//BtoPvec[player.movenum] = pnum[0]->g_posNum[player.movenum] - player.g_posPlayer;

	//D3DXVec3Normalize(&norBtoP, &BtoPvec[player.movenum]);

	//BtoPLen = D3DXVec3Length(&BtoPvec[player.movenum]);

	////����
	//D3DXVECTOR3 attracsion = norBtoP * (FLOAT)2.0;


	////�ړ���ւ̋�����2�ȏゾ�����ꍇ�Ɉړ�
	////���͂̐����ɒ���

	//if (BtoPLen >= 2) {
	//	player.g_posPlayer += attracsion;

	//}
	//else {
	//	//1�ȉ��̏ꍇ�ړ��A���͂��󂯕t���Ȃ��t���O�������i�ړ��j
	//	player.move_wait = true;
	//}


	//��M�����ł������m�F�p�A�e�L�X�g�\���Ȃ̂ŏ���
	if (pplayer_c->flag == true) {
		pplayer_c->flag_count++;
		if (pplayer_c->flag_count >= 30) {
			pplayer_c->flag = false;
			pplayer_c->flag_count = 0;
		}
	}

	SetVertex();

}



//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	DrawTEXT();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture( 0, player.g_pD3DTexturePlayer );

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, player.g_vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���W�̐ݒ�
	player.g_vertexWk[0].vtx = D3DXVECTOR3(player.g_posPlayer.x, player.g_posPlayer.y, player.g_posPlayer.z);
	player.g_vertexWk[1].vtx = D3DXVECTOR3(player.g_posPlayer.x + TEXTURE_SAMPLE00_SIZE_X, player.g_posPlayer.y, player.g_posPlayer.z);
	player.g_vertexWk[2].vtx = D3DXVECTOR3(player.g_posPlayer.x, player.g_posPlayer.y +TEXTURE_SAMPLE00_SIZE_Y, player.g_posPlayer.z);
	player.g_vertexWk[3].vtx = D3DXVECTOR3(player.g_posPlayer.x + TEXTURE_SAMPLE00_SIZE_X, player.g_posPlayer.y + TEXTURE_SAMPLE00_SIZE_Y, player.g_posPlayer.z);

	// rhw�̐ݒ�
	player.g_vertexWk[0].rhw =
	player.g_vertexWk[1].rhw =
	player.g_vertexWk[2].rhw =
	player.g_vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	player.g_vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	player.g_vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	player.g_vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	player.g_vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	player.g_vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	player.g_vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	player.g_vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	player.g_vertexWk[3].tex = D3DXVECTOR2(0.2f, 1.0f);

	

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTexturePlayer( int cntPattern )
{
	// �e�N�X�`�����W�̐ݒ�
	//�p�^�[���ԍ�����e�N�X�`�����W���v�Z,TEXTURE_PATTERN_DIVIDE_X = 8
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X;
	int y = cntPattern % TEXTURE_PATTERN_DIVIDE_X;
	//TEXTURE_PATTERN_DIVIDE_Y = 1
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y;
	//�e�N�X�`�����W�̍X�V
	player.g_vertexWk[0].tex = D3DXVECTOR2((float)(x)*sizeX, (float)(y)*sizeY);
	//�E��1�����邾���isizeX+sizeX�j
	player.g_vertexWk[1].tex = D3DXVECTOR2((float)(x)*sizeX + sizeX, (float)(y)*sizeY);
	player.g_vertexWk[2].tex = D3DXVECTOR2((float)(x)*sizeX, (float)(y)*sizeY + sizeY);
	player.g_vertexWk[3].tex = D3DXVECTOR2((float)(x)*sizeX + sizeX, (float)(y)*sizeY + sizeY);
}

void SetVertex(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���W�̐ݒ�
	player.g_vertexWk[0].vtx = D3DXVECTOR3(player.g_posPlayer.x, player.g_posPlayer.y, player.g_posPlayer.z);
	player.g_vertexWk[1].vtx = D3DXVECTOR3(player.g_posPlayer.x + TEXTURE_SAMPLE00_SIZE_X, player.g_posPlayer.y, player.g_posPlayer.z);
	player.g_vertexWk[2].vtx = D3DXVECTOR3(player.g_posPlayer.x, player.g_posPlayer.y + TEXTURE_SAMPLE00_SIZE_Y, player.g_posPlayer.z);
	player.g_vertexWk[3].vtx = D3DXVECTOR3(player.g_posPlayer.x + TEXTURE_SAMPLE00_SIZE_X, player.g_posPlayer.y + TEXTURE_SAMPLE00_SIZE_Y, player.g_posPlayer.z);
}

void DrawTEXT(void)
{

	RECT rect2 = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	TCHAR str[256];

	if (pplayer_c->flag == true) {
		wsprintf(str, _T("\n\nbomb"));

		// �e�L�X�g�`��
		g_pD3DXFont->DrawText(NULL, str, -1, &rect2, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	}
}

PLAYER* GetPlayer() {
	return &player;
}