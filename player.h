//=====================================
//
//�v���C���[�w�b�_[player.h]
//Author:GP12B332 12 ����
//
//=====================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "Framework/MeshContainer.h"

/**************************************
�}�N����`
***************************************/
enum class PlayerState;

/**************************************
�v���C���[�N���X��`
***************************************/
class Player
{
public:
	MeshContainer* meshPlayer;

	D3DXVECTOR3			pos;				// ���݂̈ʒu
	D3DXVECTOR3			move;				// �ړ���
	D3DXVECTOR3			scl;				// ���f���̑傫��(�X�P�[��)
	D3DXVECTOR3			rot;				// ���݂̌���
	D3DXVECTOR3			rotDest;			// �ړI�̌���
	D3DXQUATERNION		Quaternion;

	D3DXVECTOR3			initpos;			// �ړ��O�ʒu
	D3DXVECTOR3			goalpos;			// �ړ���ʒu
	int					cntFrame;

	PlayerState			CurrentState;


	//�֐�
	void Init();
	void Uninit();
	void Update();
	void Draw();


	// �ړ���m�ۗp�̃i���o�[
	int goal;

};

#endif
