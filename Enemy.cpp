//=====================================
//
//�G�̏��� [Enemy.cpp]
//
//Author:�n�@�O��
//=====================================
#include "Enemy.h"
#include "debugWindow.h"

#include  <math.h>
#include "Framework\Easing.h"
#include "Framework\ResourceManager.h"

using namespace std;

/**************************************
�}�N����`
***************************************/
#define ENEMY_MODEL  "data/MODEL/airplane000.x"

#define ENEMY_FALSE (300)				//false�̎���(�������ς����Ă���)
#define ENEMY_FALSE_SNAKE	(900)

#define	ENEMY_ATTENUATION (0.98f)		//�����W�� 

#define POSDEST_MAX (6)

#define FRAMEDEST_MAX (5)

#define ENEMY_FRAME_SNAKE (200)

/****************************************
static�ϐ�
****************************************/
UINT Enemy::m_InstanceCount;

/****************************************
�R���X�g���N�^
****************************************/
Enemy::Enemy()
{
	m_InstanceCount++;
	ResourceManager::Instance()->GetMesh("Enemy", &m_pMesh);
}

/****************************************
�f�X�g���N�^
****************************************/
Enemy::~Enemy()
{
	m_InstanceCount--;
}

//EnemyStraight
/****************************************
�R���X�g���N�^
****************************************/
EnemyStraight::EnemyStraight()
{

}

/****************************************
�f�X�g���N�^
****************************************/
EnemyStraight::~EnemyStraight()
{

}

/****************************************
����������
****************************************/
HRESULT  EnemyStraight::VInit(void)
{
	m_Active = false;

	m_FrameDest = 0.0f;
	m_Scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_Dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_PosDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_CntFrame = 0.0f;
	
	m_Start =  D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	return S_OK;
}
/****************************************
�I������
*****************************************/
void EnemyStraight::VUninit(void)
{
	m_Active = false;

}
/****************************************
�X�V����
*****************************************/
void EnemyStraight::VUpdate(void)
{
	if (m_Active)
	{
		if (m_CntFrame <= m_FrameDest )
		{
			//�u���[�L�̎�G��
			m_Pos = Easing<D3DXVECTOR3>::GetEasingValue((m_CntFrame/m_FrameDest), &m_Start, 
				&m_PosDest, EasingType::InCubic);
			
		}

		
		//count����.
		m_CntFrame++;
	}
}

/****************************************
�`�揈��
*****************************************/
void EnemyStraight::VDraw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;

	if (m_Active)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&mtxWorld);

		// �X�P�[���𔽉f
		D3DXMatrixScaling(&mtxScl, m_Scl.y, m_Scl.x, m_Scl.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Rot.y, m_Rot.x, m_Rot.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTranslate, m_Pos.x, m_Pos.y, m_Pos.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

		m_pMesh->Draw();
	}

}
/****************************************
�Z�b�g����
*****************************************/

void EnemyStraight::VSet(D3DXVECTOR3 start, D3DXVECTOR3 end, int frame)
{

	m_FrameDest = frame;
	m_PosDest = end;
	
	m_Start = m_Pos = start;
	m_CntFrame = 0.0f;
	
	m_Active = true;
}




//EnemyChange
/****************************************
�R���X�g���N�^
****************************************/
EnemyChange::EnemyChange()
{

}

/****************************************
�f�X�g���N�^
****************************************/
EnemyChange::~EnemyChange()
{

}

/****************************************
����������
****************************************/
HRESULT EnemyChange::VInit(void)
{
	m_Active = false;


	m_Pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_RotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_CntFrame = 0.0f;

	m_FrameDest = 0.0f;
	m_Dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_PosDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_Start = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_waitTime = 0.0f;
    m_VecChange = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	return S_OK;
}
/****************************************
�I������
*****************************************/
void EnemyChange::VUninit()
{
	m_Active = false;
}

/****************************************
�X�V����
*****************************************/
void EnemyChange::VUpdate()
{
	if (m_Active)
	{

		if (m_CntFrame > m_FrameDest + m_waitTime + ENEMY_FALSE)
		{
			m_Active = false;
		}

		if (m_CntFrame > m_FrameDest && m_CntFrame < m_FrameDest + m_waitTime)
		{

		}
		else if (m_CntFrame == m_FrameDest + m_waitTime)
		{
			m_Move = m_VecChange;
			
		}
		else if (m_CntFrame > m_FrameDest + m_waitTime)
		{

			//move = vecChange;

			//�N�I���e�B�A�b�v����?
			m_Move *= ENEMY_ATTENUATION;
			m_Pos += m_Move;
		}
		else if (m_CntFrame < m_FrameDest)
		{
			//�u���[�L�̎�G��
			m_Pos = Easing<D3DXVECTOR3>::GetEasingValue((m_CntFrame / m_FrameDest), &m_Start,
				&m_PosDest, EasingType::OutCubic);
			
		}
		//count����
		m_CntFrame++;
	}
}

/****************************************
�`�揈��
*****************************************/
void EnemyChange::VDraw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;

	if (m_Active)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&mtxWorld);

		// �X�P�[���𔽉f
		D3DXMatrixScaling(&mtxScl, m_Scl.y, m_Scl.x, m_Scl.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Rot.y, m_Rot.x, m_Rot.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTranslate, m_Pos.x, m_Pos.y, m_Pos.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

		m_pMesh->Draw();
	}
}

/****************************************
�Z�b�g����
*****************************************/
void EnemyChange::VSet(D3DXVECTOR3 start, D3DXVECTOR3 end, int frame)
{
	//��
}

void EnemyChange::VSetVec(D3DXVECTOR3 start, D3DXVECTOR3 end, int frame, int waitTime, D3DXVECTOR3 vec)
{
	m_VecChange = vec;
	m_waitTime = waitTime;
	m_FrameDest = frame;
	m_PosDest = end;
	
	m_Start = start;
	

	m_Active = true;
}



//EnemySnake
/****************************************
�R���X�g���N�^
****************************************/
EnemySnake::EnemySnake()
{
	
}

/****************************************
�f�X�g���N�^
****************************************/
EnemySnake::~EnemySnake()
{

}

/****************************************
����������
****************************************/
HRESULT EnemySnake::VInit()
{
	m_Active = false;

	m_WaitTime = 0;
	m_CurrentIndex = 0;
	m_posDestMax = 0;

	//for (int i = 0; i < POSDEST_MAX; i++)
	//{
	//	//�d�l���̃C���[�W�}�ƈႤ�AE��m_PosDestList[0]
	//	m_PosDestList.push_back(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//	
	//}
	
	//for (int i = 0; i < FRAMEDEST_MAX; i++)
	//{
	//	//m_FrameDestList[0]-->m_PosDestList[1]
	//	m_FrameDestList.push_back(0.0f);

	//}

	m_Pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_RotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	m_FrameDest = 0.0f;
	m_Dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_PosDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_CntFrame = 0.0f;

	m_Start = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	return S_OK;
}

/****************************************
�I������
*****************************************/
void EnemySnake::VUninit()
{
	m_Active = false;
}

/****************************************
�X�V����
*****************************************/
void EnemySnake::VUpdate()
{
	//�O�̓_��ʉ߂���̂ɂ̎���
	static int framePassed = 0;
	//��~��Ԃ̃t���[�����J�E���g
	static int waitcount = 0;

	//�Ō�̓_�̃t���[��
	int last = framePassed + m_FrameDestList[m_posDestMax - 2];

	if (m_Active)
	{
		if (m_CntFrame == last && m_CurrentIndex == m_posDestMax-2)
		{
			//���̂܂ܐi��
			m_Move =(m_PosDestList[m_posDestMax - 1] - m_PosDestList[m_posDestMax - 2])/ ENEMY_FRAME_SNAKE;
			
		}
		else if (m_CntFrame >= last && m_CurrentIndex == m_posDestMax - 2)
		{
			//�������I�������
			if (m_CntFrame >= last + ENEMY_FALSE_SNAKE)
			{
				m_Active = false;
			}
			m_Pos += m_Move;
		}//��~
		else if ((m_CntFrame > (framePassed + m_FrameDestList[m_CurrentIndex])) && m_CurrentIndex <= m_posDestMax - 2)
		{
			//��~���̃t���[�����ꎞ�ۑ�����
			waitcount++;
			//��~�̎��Ԃ��߂�����
			if (waitcount == m_WaitTime)
			{
				//��~�̎��Ԃ��J�E���^�[�ɓ����
				framePassed = m_CntFrame;
				waitcount = 0;
			}
		}//���̓_�ɒ�������
		else if ((m_CntFrame == (framePassed + m_FrameDestList[m_CurrentIndex])) && m_CurrentIndex <= m_posDestMax - 2)
		{
			//index�����̓_�Ɏw��
			m_CurrentIndex++;
			//���܂ł̏��v���Ԃ��L�^
			framePassed = m_CntFrame;
		}
		else if (m_CurrentIndex <= m_posDestMax - 2)
		{
			m_Pos = Easing<D3DXVECTOR3>::GetEasingValue(((m_CntFrame - framePassed) / m_FrameDestList[m_CurrentIndex]),
				&m_PosDestList[m_CurrentIndex], &m_PosDestList[m_CurrentIndex + 1], EasingType::OutCubic);
		}

		//count����
		m_CntFrame++;

	}
}

/****************************************
�`�揈��
*****************************************/
void EnemySnake::VDraw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;

	if (m_Active)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&mtxWorld);

		// �X�P�[���𔽉f
		D3DXMatrixScaling(&mtxScl, m_Scl.y, m_Scl.x, m_Scl.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Rot.y, m_Rot.x, m_Rot.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTranslate, m_Pos.x, m_Pos.y, m_Pos.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

		m_pMesh->Draw();
	}
}

/****************************************
�Z�b�g����
*****************************************/
void EnemySnake::VSet(D3DXVECTOR3 start, D3DXVECTOR3 end1, int frame)
{
	//��
}

void EnemySnake::Set(vector<D3DXVECTOR3> posDestList, vector<float> frameDestList,int waitTime)
{
	
	m_PosDestList = posDestList;
	m_FrameDestList = frameDestList;
	m_WaitTime = waitTime;

	m_posDestMax = m_PosDestList.size();

	m_Active = true;
}