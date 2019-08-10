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
#define SHADOW_MAX      (8)						//�V���h�E��
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

	bool				m_Active;			//�A�N�e�B�u

	D3DXVECTOR3			m_Scl;				//���f���̑傫��(�X�P�[��)
	D3DXVECTOR3			m_Rot;				//���݂̌���
	D3DXVECTOR3			m_Pos;				//���݂̈ʒu

	D3DXVECTOR3			m_Move;				//�ړ���
	D3DXVECTOR3         m_Dir;				//�ړ��̕���
	D3DXVECTOR3         m_PosDest;			//�ړ���
	D3DXVECTOR3         m_Start;			//�ړ��̌�
	float				m_FrameDest;	    //�ړ�������t���[����

	D3DXVECTOR3			m_RotDest;			//�ړI�̌���
	int					m_CntFrame;			//�t���[���J�E���g
	

	//�������z�֐�
	virtual HRESULT  VInit(void) = 0;
	virtual void VUninit(void) = 0;
	virtual void VUpdate(void) = 0;
	virtual void VDraw(void) = 0;
	virtual void VSet(D3DXVECTOR3 start, D3DXVECTOR3 end, int frame) = 0;	//�Z�b�g����
	virtual void VSetVec(D3DXVECTOR3 start, D3DXVECTOR3 end, int frame, int time, D3DXVECTOR3 vec) {};

	//static�����o
	MeshContainer *m_pMesh;
	static UINT m_InstanceCount;
};

class EnemyStraight : public Enemy
{
public:
	float m_SclTime;								//�A�j���[�V�����̎���

	int	  position_history_timer;					//���O�̃t���[���̎���

	int   position_history_index;					//�V���h�E���[�N�̃C���f�N�X

	D3DXVECTOR3			m_ShadowPos[SHADOW_MAX];	//�L���[�\��		
	D3DXVECTOR3			m_ShadowScl[SHADOW_MAX];

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

	int				m_WaitTime;		//��~�̎���
	D3DXVECTOR3		m_VecChange;	//��~���Ĉȍ~�̃x�N�g��
	float			m_SclTime;		//�A�j���[�V�����̎���
	bool			m_Expansion;	//true:�g��  false:�k��
	
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
	int m_PrevIndex;					//1�t���[���O��posDestList�̉��Ԃ֌������Ă�����
	int m_PosDestMax;					//m_FrameDestList�̗v�f��
	int m_FramePassed;					//�O�̓_��ʉ߂���̂ɂ̎���
	int m_WaitCount;					//��~��Ԃ̃t���[�����J�E���g

	vector<D3DXVECTOR3> m_PosDestList;  //�ړ���Am_PosDestList[0]��E����J�E���g
	vector<int> m_FrameDestList;		//�ړ�������t���[�����@m_PosDestList[1]�ɂ��鎞�A m_FrameDestList[0]

	EnemySnake();
	~EnemySnake();

	HRESULT VInit(void);
	void VUninit(void);
	void VUpdate(void);
	void VDraw(void);

	void VSet(D3DXVECTOR3 start, D3DXVECTOR3 end, int frame);

	//�X�^�[�g�̏�(posDestList[0])�@
	//[1]�ړ��悲�Ƃɐݒ�A[2]posDestList�̉��Ԃ̈ړ�������t���[�����ɐݒ�A[3]��~�̎���
	void Set(vector<D3DXVECTOR3> posDestList, vector<int> m_frameDestList,int m_waitTime);
	
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


#endif
