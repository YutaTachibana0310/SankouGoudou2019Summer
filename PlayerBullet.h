//=====================================
//
//�o���b�g�w�b�_[PlayerBullet.h]
//Author:GP12B332 12 ����
//
//=====================================
#ifndef _PLAYERBULLET_H_
#define _PLAYERBULLET_H_

#include "main.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/

/**************************************
�v���g�^�C�v�錾
***************************************/
class PlayerBullet
{
public:

	// �ϐ�
	D3DXVECTOR3			pos;				// ���݂̈ʒu
	D3DXVECTOR3			move;				// �ړ���
	D3DXVECTOR3			scl;				// ���f���̑傫��(�X�P�[��)
	D3DXVECTOR3			rot;				// ���݂̌���
	D3DXVECTOR3			rotDest;			// �ړI�̌���

	// �֐�
	void Init();
	void Uninit();
	void Update();
	void Draw();
};

#endif