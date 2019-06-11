#include "BackGroundRoad.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_FIELD	"data/TEXTURE/BG/road.jpg"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define NUM_FIELD (1)
#define BACKGROUNDROAD_POS_RANGE_X      (600.0f)
#define BACKGROUNDROAD_POS_RANGE_Y      (-1000.0f)
#define BACKGROUNDROAD_POS_RANGE_Z      (10000.0f)
#define BACKGROUNDROAD_NUM_MAX			(100)

#define BACKGROUNDROAD_MOVE_SPEED	    (-0.03f)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureRoad = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffRoad = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
//OBJECT3D	Field[NUM_FIELD];			

D3DXMATRIX				g_mtxWorldRoad;			// ���[���h�}�g���b�N�X
D3DXVECTOR3				g_posRoad;					// ���݂̈ʒu
D3DXVECTOR3				g_rotRoad;					// ���݂̌���



//=============================================================================
// ����������
//=============================================================================
HRESULT InitBackGroundRoad(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	HRESULT hr;

	// �ʒu�A�����̏����ݒ�
	g_posRoad = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotRoad = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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
	D3DXMATRIX mtxeRot, mtxeTranslate;


	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldRoad);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxeRot, g_rotRoad.y, g_rotRoad.x, g_rotRoad.z);
	D3DXMatrixMultiply(&g_mtxWorldRoad, &g_mtxWorldRoad, &mtxeRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxeTranslate, g_posRoad.x, g_posRoad.y, g_posRoad.z);
	D3DXMatrixMultiply(&g_mtxWorldRoad, &g_mtxWorldRoad, &mtxeTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldRoad);

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
		pVtx[0].vtx = D3DXVECTOR3(-BACKGROUNDROAD_POS_RANGE_X, BACKGROUNDROAD_POS_RANGE_Y, BACKGROUNDROAD_POS_RANGE_Z );//����
		pVtx[1].vtx = D3DXVECTOR3(BACKGROUNDROAD_POS_RANGE_X, BACKGROUNDROAD_POS_RANGE_Y, BACKGROUNDROAD_POS_RANGE_Z );//�E��
		pVtx[2].vtx = D3DXVECTOR3(-BACKGROUNDROAD_POS_RANGE_X, BACKGROUNDROAD_POS_RANGE_Y, -BACKGROUNDROAD_POS_RANGE_Z );//����O
		pVtx[3].vtx = D3DXVECTOR3(BACKGROUNDROAD_POS_RANGE_X, BACKGROUNDROAD_POS_RANGE_Y, -BACKGROUNDROAD_POS_RANGE_Z );//�E��O

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
		pVtx[2].tex = D3DXVECTOR2(0.0f, 25.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 25.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffRoad->Unlock();

	}
	return S_OK;
}

//OBJECT3D* GetField(int no)
//{
//	return &Field[no];
//}