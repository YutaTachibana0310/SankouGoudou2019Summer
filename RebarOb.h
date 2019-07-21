//=============================================================================
//
// ���f������ [model.h]
// Author : �����̎���
//
//=============================================================================
#ifndef _REBAROB_H_
#define _REBAROB_H_


#include "main.h"



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitRebarOb(void);
void UninitRebarOb(void);
void UpdateRebarOb(void);
void DrawRebarOb(void);
void ResetRebar(int no);
void SetRebar(D3DXVECTOR3 pos);


typedef struct
{
	//�|���S��X�t�@�C�����f��1���̏��
	LPDIRECT3DTEXTURE9	m_pD3DTextureRebarob;		// �e�N�X�`���֏��̃|�C���^
	LPD3DXMESH			m_pD3DXMeshRebarob;		// ���b�V�����ւ̃|�C���^
	LPD3DXBUFFER		m_pD3DXBuffMatRebarob;	// �}�e���A�����ւ̃|�C���^
	DWORD				m_nNumMatRebarob;			// �}�e���A�����̐�


}REBAROB3D;

typedef struct
{

	D3DXMATRIX			m_mtxWorld;				// ���[���h�}�g���b�N�X

	D3DXVECTOR3			m_posRebarOb;				// ���f���̈ʒu
	D3DXVECTOR3			m_rotRebarOb;				// ���f���̌���(��])
	D3DXVECTOR3			m_sclRebarOb;				// ���f���̑傫��(�X�P�[��)
	D3DXVECTOR3			m_vecRebarOb;             //�G�l�~�[�̃x�N�g��

	D3DXVECTOR3			m_DirSpeed;				//�ړ��x�N�g��
	D3DXVECTOR3			m_RotSpeed;				//��]�X�s�[�h
	D3DXVECTOR3			m_Kakudo;				//��]�ړ��p�p�x
	D3DXVECTOR3			m_Radius;				//��]�ړ��p���a

	bool                m_bUse;                 //���̃I�u�W�F�N�g���g�p��Ԃ�

	int					m_RebarObID;				// ���̃L�����N�^�̃��f���f�[�^��ID
	int					m_ShadowID;				// ���̃L�����N�^�̉e�I�u�W�F�N�g��ID
}OBJECT3D;

OBJECT3D* GetRebarOb(int no);//�\���̂̐擪�|�C���^���擾
#endif
