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
	bool bUse;

	
	MeshContainer* meshPlayer;

	/*Enemy();
	virtual ~Enemy();*/
	D3DXVECTOR3			pos;				// ���݂̈ʒu
	D3DXVECTOR3			move;				// �ړ���
	D3DXVECTOR3			scl;				// ���f���̑傫��(�X�P�[��)
	D3DXVECTOR3			rot;				// ���݂̌���
	D3DXVECTOR3			rotDest;			// �ړI�̌���

	int					cntFrame;			//�t���[���J�E���g
	//�������z�֐�
	virtual HRESULT  Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	virtual void Set(D3DXVECTOR3 pos) = 0;	//�Z�b�g����
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

	void Set(D3DXVECTOR3 pos);
	
};

class EnemyChange :public Enemy
{
public:

	EnemyChange();
	~EnemyChange();
	HRESULT  Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Set(D3DXVECTOR3 pos);
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


#endif
