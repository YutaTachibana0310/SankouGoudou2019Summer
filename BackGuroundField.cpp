#include "BackGroundField.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_FIELD	"data/TEXTURE/BG/road.jpg"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define BACKGROUNDFIELD_SIZE			(15000.0f)
#define BACKGROUNDFIELD_POS_Y			(-2500.0f)

#define BACKGROUNDFIELD_MOVE_SPEED	    (-25.0f)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureField = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffField = NULL;	// ���_�o�b�t�@�ւ̃|�C���^

D3DXVECTOR3				posField;					// ���݂̈ʒu

//=============================================================================
// ����������
//=============================================================================
HRESULT InitBackGroundField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	HRESULT hr;

	// �ʒu�A�����̏����ݒ�
	posField = D3DXVECTOR3(0.0f, BACKGROUNDFIELD_POS_Y, 0.0f);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
		TEXTURE_FIELD,			// �t�@�C���̖��O
		&g_pD3DTextureField);	// �ǂݍ��ރ������[

								// ���_���̍쐬
	hr = MakeVertexBackGroundField(pDevice);

	return hr;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBackGroundField(void)
{
	if (g_pD3DTextureField != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureField->Release();
		g_pD3DTextureField = NULL;
	}

	if (g_pD3DVtxBuffField != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffField->Release();
		g_pD3DVtxBuffField = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBackGroundField(void)
{
	VERTEX_3D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pD3DVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].tex.y += BACKGROUNDFIELD_MOVE_SPEED;//����
	pVtx[1].tex.y += BACKGROUNDFIELD_MOVE_SPEED;//�E��
	pVtx[2].tex.y += BACKGROUNDFIELD_MOVE_SPEED;//����O
	pVtx[3].tex.y += BACKGROUNDFIELD_MOVE_SPEED;//�E��O

	g_pD3DVtxBuffField->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBackGroundField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxeTranslate, mtxWorld;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxeTranslate, posField.x, posField.y, posField.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxeTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pD3DVtxBuffField, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureField);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexBackGroundField(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_3D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffField,		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		g_pD3DVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(-BACKGROUNDFIELD_SIZE, 0.0f, BACKGROUNDFIELD_SIZE);
		pVtx[0].vtx = D3DXVECTOR3( BACKGROUNDFIELD_SIZE, 0.0f, BACKGROUNDFIELD_SIZE);
		pVtx[0].vtx = D3DXVECTOR3(-BACKGROUNDFIELD_SIZE, 0.0f, -BACKGROUNDFIELD_SIZE);
		pVtx[0].vtx = D3DXVECTOR3( BACKGROUNDFIELD_SIZE, 0.0f, -BACKGROUNDFIELD_SIZE);

        // �@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 50.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 50.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffField->Unlock();

	}
	return S_OK;
}