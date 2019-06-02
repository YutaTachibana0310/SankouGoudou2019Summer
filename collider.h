//=============================================================================
//
// �����蔻��p���� [collider.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _COLLIDER_
#define _COLLIDER_

// �J�[�\���̓����蔻��p�̃T�[�N��
#define COLLIDERSIZE_X_CURSOR (5)
#define COLLIDERSIZE_Y_CURSOR (5)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
bool IsHittedBB(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2);
bool IsHittedBC(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2);

#endif

