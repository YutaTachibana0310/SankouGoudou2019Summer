//=====================================
//
//�e���v���[�g�w�b�_[debugTimer.h]
//===================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "Framework/MeshContainer.h"


#define PLAYER_INIT_POS		D3DXVECTOR3(0.0 ,-50.0, 150.0)

#define MAX_LENGTH (6)

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


	/****************************/
	//�n糂��񑤂ɂ����������o
	/*****************************/
	LPDIRECT3DTEXTURE9		D3DTexturePlayer = NULL;		// �e�N�X�`���ւ̃|���S��

	VERTEX_2D				vertexWk[NUM_VERTEX];				// ���_���i�[���[�N

	D3DXVECTOR3				posPlayer;						// �|���S���̈ړ���
	D3DXVECTOR3				targetpos[MAX_LENGTH];

	// �ړ���m�ۗp�̃i���o�[
	int goal;

	HRESULT MakeVertexPlayer(void);
	void SetVertex(void);
};


#endif
