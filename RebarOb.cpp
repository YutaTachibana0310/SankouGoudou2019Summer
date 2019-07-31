//=============================================================================
//
// ���f������ [player.cpp]
// Author : �����̎���
//
//	�����L�����N�^�Ή���
//
//=============================================================================
#include "RebarOb.h"
//

////*****************************************************************************
//// �}�N����`
////*****************************************************************************
OBJECT3D* rebarob = GetRebarOb(0);

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
D3DXVECTOR3 axis;//��]��
D3DXMATRIX mtxeScl, mtxeRot, mtxeTranslate;

//*************�L�����N�^�[�f�[�^�ϐ��̗p��*****************************
#define		NUM_REBAROB	(1)//���f���̐�

#define     REBAR_POS_X (0.0f)
#define     REBAR_POS_Y (2.0f)
#define     REBAR_POS_Z (500.0f)

#define     REBAR_ROT_X (0.0f)
#define     REBAR_ROT_Y (0.0f)
#define     REBAR_ROT_Z (0.0f)

#define     REBAR_SCL_X (1.0f)
#define     REBAR_SCL_Y (1.0f)
#define     REBAR_SCL_Z (1.0f)

#define     REBAR_VEC_X (0.0f)
#define     REBAR_VEC_Y (0.0f)
#define     REBAR_VEC_Z (1.0f)

#define     MOVE_SPEED (-1.0)

#define     REBAR_MOVE (0.1f)
OBJECT3D	RebarOB[NUM_REBAROB];//�G�l�~�[�\����

float rotValue = 0.0f;//���f���̉�]�p
float Valuerotation = 0.05f;//���f���̉�]���x
float lostpos = -50.0f;//���f����������i�񂾂������

//*************���f���[�f�[�^�ϐ��̗p��*****************************

REBAROB3D		RebarOb[NUM_REBAROB];		//���f���\����

//*********************���f���f�[�^�t�@�C�����z��********************
const char* RebarobData[] =
{
	"data/MODEL/redar.x",

};






//=============================================================================
// ����������
//=============================================================================
HRESULT InitRebarOb(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���C�g�̏�����
	//InitLight();
	// �L�����N�^�̈ʒu�E��]�E�X�P�[���Ȃǂ̏����ݒ�
	for (int i = 0; i < NUM_REBAROB; i++)
	{
		RebarOB[i].m_posRebarOb = D3DXVECTOR3(REBAR_POS_X, REBAR_POS_Y, REBAR_POS_Z);
		RebarOB[i].m_rotRebarOb = D3DXVECTOR3(REBAR_ROT_X, REBAR_ROT_Y, REBAR_ROT_Z);
		RebarOB[i].m_sclRebarOb = D3DXVECTOR3(REBAR_SCL_X, REBAR_SCL_Y, REBAR_SCL_Z);
		RebarOB[i].m_vecRebarOb = D3DXVECTOR3(REBAR_VEC_X, REBAR_VEC_Y, REBAR_VEC_Z);

		RebarOB[i].m_RebarObID = 0;

	}
	for (int i = 0; i < NUM_REBAROB; i++)
	{
		RebarOB[i].m_RebarObID = i;	//�L�����N�^[0]���g�p���郂�f���f�[�^�̔ԍ�
		D3DXVECTOR3 temp = RebarOB[i].m_posRebarOb;//�L�����N�^[0]�̉e�I�u�W�F�N�g�쐬
	}


	//���f���f�[�^�̏����ݒ�
	for (int i = 0; i < NUM_REBAROB; i++)
	{

		RebarOb[i].m_pD3DTextureRebarob = NULL;
		RebarOb[i].m_pD3DXMeshRebarob = NULL;
		RebarOb[i].m_pD3DXBuffMatRebarob = NULL;
		RebarOb[i].m_nNumMatRebarob = 0;

		RebarOB[i].m_bUse = FALSE;


		if (D3D_OK != D3DXLoadMeshFromX(RebarobData[0],			// �ǂݍ��ރ��f���t�@�C����(X�t�@�C��)
			D3DXMESH_SYSTEMMEM,		// ���b�V���̍쐬�I�v�V�������w��
			pDevice,				// IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
			NULL,					// �אڐ��f�[�^���܂ރo�b�t�@�ւ̃|�C���^
			&RebarOb[i].m_pD3DXBuffMatRebarob,	// �}�e���A���f�[�^���܂ރo�b�t�@�ւ̃|�C���^
			NULL,					// �G�t�F�N�g�C���X�^���X�̔z����܂ރo�b�t�@�ւ̃|�C���^
			&RebarOb[i].m_nNumMatRebarob,		// D3DXMATERIAL�\���̂̐�
			&RebarOb[i].m_pD3DXMeshRebarob))	// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^�̃A�h���X
		{
			return E_FAIL;
		}
	}




#if 0
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
		TEXTURE_FILENAME,		// �t�@�C���̖��O
		&g_pD3DTextureEnemy);	// �ǂݍ��ރ������[
#endif
	SetRebar(0,3);
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitRebarOb(void)
{


	for (int i = 0; i < NUM_REBAROB; i++)
	{
		if (RebarOB[i].m_bUse)
		{
			if (NULL != RebarOb[i].m_pD3DTextureRebarob)
			{
				RebarOb[i].m_pD3DTextureRebarob->Release();
				RebarOb[i].m_pD3DTextureRebarob = NULL;
			}

			if (NULL != RebarOb[i].m_pD3DXMeshRebarob)
			{
				RebarOb[i].m_pD3DXMeshRebarob->Release();
				RebarOb[i].m_pD3DXMeshRebarob = NULL;
			}

			if (NULL != RebarOb[i].m_pD3DXBuffMatRebarob)
			{
				RebarOb[i].m_pD3DXBuffMatRebarob->Release();
				RebarOb[i].m_pD3DXBuffMatRebarob = NULL;
			}
		}
	}


}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateRebarOb(void)
{

	for (int i = 0; i < NUM_REBAROB; i++)
	{
		if (RebarOB[i].m_bUse)
		{
			RebarOB[i].m_posRebarOb.z += MOVE_SPEED;
			rotValue += Valuerotation;

			if (RebarOB[i].m_posRebarOb.z <= lostpos)
			{
				RebarOB[i].m_bUse = false;
			}
		}
	}

}


//=============================================================================
// �`�揈��
//=============================================================================
void DrawRebarOb(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;

	//���C�gON
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);


	// ���ݐݒ肳��Ă���}�e���A�����擾���ĕۑ�
	pDevice->GetMaterial(&matDef);


	//*************************�S�ẴL�����N�^�[��\��************************
	for (int i = 0; i < NUM_REBAROB; i++)
	{
		if (RebarOB[i].m_bUse)
		{
			D3DXVECTOR3	temp;

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&RebarOB[i].m_mtxWorld);

			// �X�P�[�����s��ɂ��ă��[���h�s��i�n�߂͒P�ʍs��j�Ə�Z
			temp = RebarOB[i].m_sclRebarOb;
			D3DXMatrixScaling(&mtxeScl, temp.x, temp.y, temp.z);
			D3DXMatrixMultiply(&RebarOB[i].m_mtxWorld, &RebarOB[i].m_mtxWorld, &mtxeScl);

			// ��]���s��ɂ��ă��[���h�s��Ə�Z
			temp = RebarOB[i].m_rotRebarOb;
			D3DXMatrixRotationYawPitchRoll(&mtxeRot, temp.y, temp.x, temp.z);
			D3DXMatrixMultiply(&RebarOB[i].m_mtxWorld, &RebarOB[i].m_mtxWorld, &mtxeRot);

			//�N�H�[�^�j�I���ł̉�]
			D3DXQUATERNION rotQ;//��]�p�̃N�H�[�^�j�I��
			D3DXQuaternionRotationAxis(&rotQ,
										&axis,
										rotValue);
			D3DXMatrixRotationQuaternion(&mtxeRot,
				&rotQ);
			D3DXMatrixMultiply(&RebarOB[i].m_mtxWorld, &RebarOB[i].m_mtxWorld, &mtxeRot);

			// �ړ����s��ɂ��ă��[���h�s��Ə�Z
			temp = RebarOB[i].m_posRebarOb;
			D3DXMatrixTranslation(&mtxeTranslate, temp.x, temp.y, temp.z);
			//�s��̊|���Z
			D3DXMatrixMultiply(&RebarOB[i].m_mtxWorld, &RebarOB[i].m_mtxWorld, &mtxeTranslate);

			// �����������[���h�}�g���b�N�X��DirectX�փZ�b�g
			pDevice->SetTransform(D3DTS_WORLD, &RebarOB[i].m_mtxWorld);


			//���̃L�����N�^�[���g�����f����ID
			int rebarno = RebarOB[i].m_RebarObID;


			// ���f���̃}�e���A�����ɑ΂���|�C���^���擾
			pD3DXMat = (D3DXMATERIAL*)RebarOb[rebarno].m_pD3DXBuffMatRebarob->GetBufferPointer();

			//���f���̏��ɏ]���ă��f�����\������I�u�W�F�N�g�̐������J��Ԃ�
			for (int nCntMat = 0; nCntMat < (int)RebarOb[rebarno].m_nNumMatRebarob; nCntMat++)
			{
				// �I�u�W�F�N�g�̃}�e���A���̐ݒ�
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

				// �I�u�W�F�N�g�̃e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, RebarOb[rebarno].m_pD3DTextureRebarob);

				// �I�u�W�F�N�g�̕`��
				RebarOb[rebarno].m_pD3DXMeshRebarob->DrawSubset(nCntMat);
			}
		}
	}

	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);

}

void SetRebar(int a,int b)
{
	LineTrailModel model;
	D3DXVECTOR3 right, left;

	right = model.GetEdgePos(a);
	left = model.GetEdgePos(b);

	for (int i = 0; i < NUM_REBAROB; i++)
	{
		if (RebarOB[i].m_bUse == false)
		{
			RebarOB[i].m_posRebarOb = (right - left) / 2.0f + left;
			RebarOB[i].m_posRebarOb.z = REBAR_POS_Z;

			RebarOB[i].m_rotRebarOb.z = atan2f(RebarOB[i].m_posRebarOb.y - left.y, RebarOB[i].m_posRebarOb.x - left.x);

			D3DXVec3Cross(&axis,
				&D3DXVECTOR3(0, 0, 1),
				&(right - left));

			RebarOB[i].m_bUse = true;

			return;
		}
	}
}

OBJECT3D* GetRebarOb(int no)
{
	return &RebarOB[no];
}