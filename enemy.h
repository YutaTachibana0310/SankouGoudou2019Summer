//=============================================================================
//
//�G�̏��� [Enemy.h]
// 
//Author:�n�@�O��
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "Framework/MeshContainer.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************

#define MAX_ENEMY (100)



//*****************************************************************************
// ���
//*****************************************************************************


//*****************************************************************************
// �N���X��`
//*****************************************************************************
//���ۃN���X�@���܂��܂Ȕh���N���X�̃I�u�W�F�N�g���ꊇ�Ǘ��̂���
class Enemy
{
public:
	MeshContainer* meshPlayer;

	//����?
	Enemy();
	virtual ~Enemy();

	bool				active;				//�A�N�e�B�u

	D3DXVECTOR3			pos;				//���݂̈ʒu
	D3DXVECTOR3			move;				//�ړ���
	D3DXVECTOR3			scl;				//���f���̑傫��(�X�P�[��)
	D3DXVECTOR3			rot;				//���݂̌���
	D3DXVECTOR3			rotDest;			//�ړI�̌���

	D3DXVECTOR3         dir;				//�ړ��̕���
	D3DXVECTOR3         posDest;			//�ړ���

	int					cntFrame;			//�t���[���J�E���g
	int					frameDest;
	//�������z�֐�
	virtual HRESULT  Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	virtual void Set(D3DXVECTOR3 start, D3DXVECTOR3 end, int frame) = 0;	//�Z�b�g����
	virtual void SetVec(D3DXVECTOR3 start, D3DXVECTOR3 end, int frame, int time, D3DXVECTOR3 vec) {};
};


class EnemyStraight : public Enemy
{
public:

	EnemyStraight();
	~EnemyStraight();
	HRESULT  Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Set(D3DXVECTOR3 start, D3DXVECTOR3 end, int frame);
	
};

class EnemyChange :public Enemy
{
public:

	int m_waitTime;			//��~�̎���
	D3DXVECTOR3 vecChange;	//��~���Ĉȍ~�̃x�N�g��

	EnemyChange();
	~EnemyChange();
	HRESULT  Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Set(D3DXVECTOR3 start, D3DXVECTOR3 end, int frame);
	void SetVec(D3DXVECTOR3 start, D3DXVECTOR3 end, int frame,int waitTime, D3DXVECTOR3 vec);

};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


#endif
