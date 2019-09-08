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
#include "Framework\BoxCollider3D.h"
#include "Framework\ColliderObserver.h"
#include <vector>

using namespace std;
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SHADOW_MAX      (8)						//�V���h�E��

//*****************************************************************************
// ���
//*****************************************************************************
class PlayerBomber;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
//���ۃN���X�@���܂��܂Ȕh���N���X�̃I�u�W�F�N�g���ꊇ�Ǘ��̂���
class Enemy : public ColliderObserver
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
	float				m_CntFrame;			//�t���[���J�E���g

	//�A�j���[�V����
	bool				m_AnimationActive;	//�A�j���[�V�����𓮂�����
	bool                m_Expansion;		//�g�傩�k����
	float				m_SclRate;			//�X�P�[���̊���
	float				m_SclSpeed;			//�X�P�[���̑���
	
	bool				m_FlgDestroyed;		//���j����
	void OnNotified(BoxCollider3DTag other);//�Փ˔���ʒm���V�[�o�[
	void OnHitBomber();						//�{���o�[���e���̃R�[���o�b�N

	//�������z�֐�
	virtual HRESULT  VInit(void) = 0;
	virtual void VUninit(void) = 0;
	virtual void VUpdate(void) = 0;
	virtual void VDraw(void) = 0;
	virtual void VSet(D3DXVECTOR3 start, D3DXVECTOR3 end, float frame) = 0;	//�Z�b�g����

	virtual void VSetVec(D3DXVECTOR3 start, D3DXVECTOR3 end, float frame, float time, D3DXVECTOR3 vec) {};
	int Animation();

	//�A�j���[�V����
	void SetAnimation(bool active, bool expansion, float sclRate,float speed);

	//static�����o
	MeshContainer *m_pMesh;
	static UINT m_InstanceCount;

protected:
	BoxCollider3D* m_Collider;
};

class EnemyStraight : public Enemy
{
public:
	//float			m_SclRate;								//�A�j���[�V�����̎���

	float			m_PositionHistoryTimer;					//���O�̃t���[���̎���
	int				m_PositionHistoryIndex;					//�V���h�E���[�N�̃C���f�N�X

	D3DXVECTOR3		m_ShadowPos[SHADOW_MAX];	            //�L���[�\��		
	D3DXVECTOR3		m_ShadowScl[SHADOW_MAX];

	EnemyStraight();
	~EnemyStraight();
	HRESULT  VInit(void);
	void VUninit(void);
	void VUpdate(void);
	void VDraw(void);

	void VSet(D3DXVECTOR3 start, D3DXVECTOR3 end, float frame);
	
};

class EnemyChange :public Enemy
{
public:

	float			m_WaitTime;		//��~�̎���
	D3DXVECTOR3		m_VecChange;	//��~���Ĉȍ~�̃x�N�g��
	
	EnemyChange();
	~EnemyChange();
	HRESULT  VInit(void);
	void VUninit(void);
	void VUpdate(void);
	void VDraw(void);

	void VSetVec(D3DXVECTOR3 start, D3DXVECTOR3 end, float frame,float waitTime, D3DXVECTOR3 vec);
	void VSet(D3DXVECTOR3 start, D3DXVECTOR3 end, float frame);

};

class EnemySnake :public Enemy
{
public:
	float			m_WaitTime;						//��~�̎���
	int				m_CurrentIndex;					//���݁AposDestList�̉��Ԃ֌������Ă��邩������ϐ�
	int				m_PrevIndex;					//1�t���[���O��posDestList�̉��Ԃ֌������Ă�����
	int				m_PosDestMax;					//m_FrameDestList�̗v�f��
	float			m_FramePassed;					//�O�̓_��ʉ߂���̂ɂ̎���
	float			m_WaitCount;					//��~��Ԃ̃t���[�����J�E���g
	UINT			m_currentColliderID;			//���ݏ������Ă���R���C�_�[��ID

	vector<D3DXVECTOR3> m_PosDestList;              //�ړ���Am_PosDestList[0]��E����J�E���g
	vector<float>	    m_FrameDestList;		    //�ړ�������t���[�����@m_PosDestList[1]�ɂ��鎞�A m_FrameDestList[0]

	EnemySnake();
	~EnemySnake();

	HRESULT VInit(void);
	void VUninit(void);
	void VUpdate(void);
	void VDraw(void);

	//�X�^�[�g�̏�(posDestList[0])�@
	//[1]�ړ��悲�Ƃɐݒ�A[2]posDestList�̉��Ԃ̈ړ�������t���[�����ɐݒ�A[3]��~�̎���
	void Set(vector<D3DXVECTOR3> posDestList, vector<float> m_frameDestList,float m_waitTime);

	void VSet(D3DXVECTOR3 start, D3DXVECTOR3 end, float frame);
	
};

class EnemyMidium : public Enemy
{
public:
	float		m_CntFrameNow;			//�t���[���J�E���g(����̈ړ����o��������)
	bool		m_Visible;				//EnemyMidium�������邩
	int			m_CntAnim;				//�A�j���[�V�����J�E���g
	
	EnemyMidium();
	~EnemyMidium();
	HRESULT VInit(void);
	void VUninit(void);
	void VUpdate(void);
	void VDraw(void);

	void Move(D3DXVECTOR3 posDest, float frameDest);
	void Set(D3DXVECTOR3 start);

	void HitAnimation();
	void SetHitAnimation();

	void VSet(D3DXVECTOR3 start, D3DXVECTOR3 end, float frame);
	
};
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


#endif
