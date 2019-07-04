#include "BackGroundRoad.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_FIELD	"data/TEXTURE/BG/road.jpg"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define BACKGROUNDROAD_SIZE_X			(600.0f)
#define BACKGROUNDROAD_SIZE_Z			(15000.0f)

#define BACKGROUNDROAD_MOVE_SPEED	    (-0.06f)

#define BACKGROUNDROAD_TEXSIZE_X		(2.0f)
#define BACKGROUNDROAD_TEXSIZE_Y		(50.0f)

#define BACKGROUNDROAD_INIT_POS_Y		(-3500.0f)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureRoad = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffRoad = NULL;	// ���_�o�b�t�@�ւ̃|�C���^

D3DXVECTOR3				posRoad;					// ���݂̈ʒu

//=============================================================================
// ����������
//=============================================================================
HRESULT InitBackGroundRoad(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	HRESULT hr;

	// �ʒu�A�����̏����ݒ�
	posRoad = D3DXVECTOR3(0.0f, BACKGROUNDROAD_INIT_POS_Y, 0.0f);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
		TEXTURE_FIELD,			// �t�@�C���̖��O
		&g_pD3DTextureRoad);	// �ǂݍ��ރ������[

								// ���_���̍쐬
	hr = MakeVertexBackGroundRoad(pDevice);

	return hr;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBackGroundRoad(void)
{
	if (g_pD3DTextureRoad != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureRoad->Release();
		g_pD3DTextureRoad = NULL;
	}

	if (g_pD3DVtxBuffRoad != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffRoad->Release();
		g_pD3DVtxBuffRoad = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBackGroundRoad(void)
{
	VERTEX_3D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pD3DVtxBuffRoad->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].tex.y += BACKGROUNDROAD_MOVE_SPEED;//����
	pVtx[1].tex.y += BACKGROUNDROAD_MOVE_SPEED;//�E��
	pVtx[2].tex.y += BACKGROUNDROAD_MOVE_SPEED;//����O
	pVtx[3].tex.y += BACKGROUNDROAD_MOVE_SPEED;//�E��O

	g_pD3DVtxBuffRoad->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBackGroundRoad(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxeTranslate, mtxWorld;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxeTranslate, posRoad.x, posRoad.y, posRoad.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxeTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pD3DVtxBuffRoad, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureRoad);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexBackGroundRoad(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_3D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffRoad,		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		g_pD3DVtxBuffRoad->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(-BACKGROUNDROAD_SIZE_X, 0.0f, BACKGROUNDROAD_SIZE_Z);
		pVtx[1].vtx = D3DXVECTOR3(BACKGROUNDROAD_SIZE_X, 0.0f, BACKGROUNDROAD_SIZE_Z);
		pVtx[2].vtx = D3DXVECTOR3(-BACKGROUNDROAD_SIZE_X, 0.0f, -BACKGROUNDROAD_SIZE_Z);
		pVtx[3].vtx = D3DXVECTOR3(BACKGROUNDROAD_SIZE_X, 0.0f, -BACKGROUNDROAD_SIZE_Z);


		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(BACKGROUNDROAD_TEXSIZE_X, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, BACKGROUNDROAD_TEXSIZE_Y);
		pVtx[3].tex = D3DXVECTOR2(BACKGROUNDROAD_TEXSIZE_X, BACKGROUNDROAD_TEXSIZE_Y);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffRoad->Unlock();

	}
	return S_OK;
}