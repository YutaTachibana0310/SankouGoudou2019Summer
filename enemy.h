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
#include <vector>

using namespace std;
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
	

	
	Enemy();
	virtual ~Enemy();

	bool				m_Active;				//�A�N�e�B�u

	D3DXVECTOR3			m_Pos;				//���݂̈ʒu
	D3DXVECTOR3			m_Move;				//�ړ���
	D3DXVECTOR3			m_Scl;				//���f���̑傫��(�X�P�[��)
	D3DXVECTOR3			m_Rot;				//���݂̌���
	D3DXVECTOR3			m_RotDest;			//�ړI�̌���

	D3DXVECTOR3         m_Dir;				//�ړ��̕���
	D3DXVECTOR3         m_PosDest;			//�ړ���

	float				m_CntFrame;			//�t���[���J�E���g

	D3DXVECTOR3         m_Start;			//�ړ��̌�

	float					m_FrameDest;	//�ړ�������t���[����
	//�������z�֐�
	virtual HRESULT  VInit(void) = 0;
	virtual void VUninit(void) = 0;
	virtual void VUpdate(void) = 0;
	virtual void VDraw(void) = 0;
	virtual void VSet(D3DXVECTOR3 start, D3DXVECTOR3 end, int frame) = 0;	//�Z�b�g����
	virtual void VSetVec(D3DXVECTOR3 start, D3DXVECTOR3 end, int frame, int time, D3DXVECTOR3 vec) {};

	//static�����o
	static MeshContainer *m_pMesh;
	static UINT m_InstanceCount;
};

class EnemyStraight : public Enemy
{
public:

	EnemyStraight();
	~EnemyStraight();
	HRESULT  VInit(void);
	void VUninit(void);
	void VUpdate(void);
	void VDraw(void);

	void VSet(D3DXVECTOR3 start, D3DXVECTOR3 end, int frame);
	
};

class EnemyChange :public Enemy
{
public:

	int m_waitTime;				//��~�̎���
	D3DXVECTOR3 m_VecChange;	//��~���Ĉȍ~�̃x�N�g��

	EnemyChange();
	~EnemyChange();
	HRESULT  VInit(void);
	void VUninit(void);
	void VUpdate(void);
	void VDraw(void);

	void VSet(D3DXVECTOR3 start, D3DXVECTOR3 end, int frame);
	void VSetVec(D3DXVECTOR3 start, D3DXVECTOR3 end, int frame,int waitTime, D3DXVECTOR3 vec);

};

class EnemySnake :public Enemy
{
public:
	int m_WaitTime;						//��~�̎���
	int m_CurrentIndex;					//���݁AposDestList�̉��Ԃ֌������Ă��邩������ϐ�
	int m_posDestMax;					//m_FrameDestList�̗v�f��

	vector<D3DXVECTOR3> m_PosDestList;  //�ړ���A�d�l���̃C���[�W�}�ƈႤ�Am_PosDestList[0]��E����J�E���g
	vector<float> m_FrameDestList;		//�ړ�������t���[�����@m_PosDestList[1]�ɂ��鎞�A m_FrameDestList[0]

	EnemySnake();
	~EnemySnake();

	HRESULT VInit(void);
	void VUninit(void);
	void VUpdate(void);
	void VDraw(void);

	void VSet(D3DXVECTOR3 start, D3DXVECTOR3 end, int frame);

	//�X�^�[�g�̏�(posDestList[0])�@
	//[1]�ړ��悲�Ƃɐݒ�A[2]posDestList�̉��Ԃ̈ړ�������t���[�����ɐݒ�A[3]��~�̎���
	void Set(vector<D3DXVECTOR3> posDestList, vector<float> m_frameDestList,int m_waitTime);
	
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


#endif
