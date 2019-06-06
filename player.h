//=====================================
//
//�e���v���[�g�w�b�_[debugTimer.h]
//===================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "Framework/MeshContainer.h"


#define PLAYER_INIT_POS		D3DXVECTOR3(0.0 ,-50.0, 150.0)


class Player
{
public:
	int currensState;
	MeshContainer* meshPlayer;

	D3DXVECTOR3			pos;				// ���݂̈ʒu
	D3DXVECTOR3			move;				// �ړ���
	D3DXVECTOR3			scl;				// ���f���̑傫��(�X�P�[��)
	D3DXVECTOR3			rot;				// ���݂̌���
	D3DXVECTOR3			rotDest;			// �ړI�̌���
	D3DXQUATERNION		Quaternion;

	D3DXVECTOR3			initpos;			// �ړ��O�ʒu
	D3DXVECTOR3			goalpos;			// �ړ���ʒu
	int			cntFrame;

	//�֐�
	void Init();
	void Uninit();
	void Update();
	void Draw();
};


#endif