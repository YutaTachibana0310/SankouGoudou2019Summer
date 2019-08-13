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
#define ENEMY_COLLIDER_SIZE	(D3DXVECTOR3(10.0f, 10.0f, 10.0f))
#define ENEMY_FALSE_CHANGE	(300)				//false�̎���(�������ς����Ă���)
#define ENEMY_FALSE_SNAKE	(900)

#define	ENEMY_ATTENUATION	(0.98f)				//�����W�� 

#define ENEMY_FRAME_SNAKE	(200)

//#define GET_RANDOM(a, b)		((a) + rand() / (RAND_MAX / ((b) - (a) + 1) + 1))

#define STRAIGHT_SCL_MIN	(D3DXVECTOR3(0.0f, 0.0f, 0.0f))  //�X�P�[���̃A�j���[�V�����̍ő�l	
#define STRAIGHT_SCL_SPEED	(0.01f)							 //�A�j���[�V�����̎��Ԃ̑���

#define CHANGE_SCL_MAX		(D3DXVECTOR3(1.0f, 1.0f, 1.0f))
#define CHANGE_SCL_MIN		(D3DXVECTOR3(0.8f, 0.8f, 0.8f))
#define CHANGE_SCL_SPEED	(0.05f)

#define WAIT_TIME			(0.9)							 //�T���v�����O����

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

	collider = new BoxCollider3D(BoxCollider3DTag::Enemy, &m_Pos);
	collider->SetSize(ENEMY_COLLIDER_SIZE);
	collider->active = true;
}

/****************************************
�f�X�g���N�^
****************************************/
Enemy::~Enemy()
{
	m_InstanceCount--;
	SAFE_DELETE(collider);
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
	m_SclTime = 0.0f;

	m_Active = false;

	m_Scl = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_PosDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Start = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_FrameDest = 0.0f;

	m_RotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_CntFrame = 0.0f;

	position_history_timer = 0;
	position_history_index = 0;

	for (int i = 0; i < SHADOW_MAX; i++)
	{
		m_ShadowPos[i] = D3DXVECTOR3(500.0f, 0.0f, 0.0f);
		m_ShadowScl[i] = m_Scl;

	}

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
		if (m_CntFrame <= m_FrameDest)
		{
			//�u���[�L�̎�G��
			m_Pos = Easing::EaseValue((float)m_CntFrame / m_FrameDest, m_Start,
				m_PosDest, EaseType::InSine);
			
			//����鎞�̊g��
			if(m_SclTime < 1.0f)
			{
				m_Scl = Easing::EaseValue(m_SclTime, STRAIGHT_SCL_MIN,
					D3DXVECTOR3(1.0f, 1.0f, 1.0f), EaseType::OutCubic);
				m_SclTime += STRAIGHT_SCL_SPEED;

				//���Ԃ���C��1.0�𒴂����ꍇ
				if (m_SclTime >= 1.0f)
				{
					m_Scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
				}
			}
		}
		else
		{
			m_Active = false;
		}

		//count����.
		m_CntFrame++;
	}

	if (m_CntFrame > position_history_timer + WAIT_TIME)
	{
		position_history_timer = m_CntFrame;
		position_history_index++;

		if (position_history_index > SHADOW_MAX - 1)
		{
			position_history_index = SHADOW_MAX - 1;
			//�L���[����
			for (int i = 1; i < SHADOW_MAX; i++)
			{
				m_ShadowPos[i - 1] = m_ShadowPos[i];
				m_ShadowScl[i - 1] = m_ShadowScl[i];
			}
				
		}
		m_ShadowPos[position_history_index] = m_Pos;
		m_ShadowScl[position_history_index] = m_Scl;
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

	for (int n = 0; n < SHADOW_MAX; n++)
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&mtxWorld);

		// �X�P�[���𔽉f
		D3DXMatrixScaling(&mtxScl, m_ShadowScl[n].y, m_ShadowScl[n].x, m_ShadowScl[n].z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTranslate, m_ShadowPos[n].x, m_ShadowPos[n].y, m_ShadowPos[n].z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

		m_pMesh->SetMaterialAlpha(float(0.07 + n * 0.039));
		m_pMesh->Draw();
		m_pMesh->SetMaterialAlpha(1.0f);
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
	m_CntFrame = 0;

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
	m_WaitTime = 0.0f;
	m_VecChange = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_SclTime = 0.0f;
	m_Expansion = true;
	m_Active = false;


	m_Pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_RotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_CntFrame = 0;

	m_FrameDest = 0;

	m_Dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_PosDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Start = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_FrameDest = 0.0f;

	m_RotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_CntFrame = 0.0f;

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

		if (m_CntFrame > m_FrameDest + m_WaitTime + ENEMY_FALSE_CHANGE)
		{
			m_Active = false;
		}

		if (m_CntFrame > m_FrameDest && m_CntFrame < m_FrameDest + m_WaitTime)
		{

		}
		else if (m_CntFrame == m_FrameDest + m_WaitTime)
		{
			m_Move = m_VecChange;

		}
		else if (m_CntFrame > m_FrameDest + m_WaitTime)
		{

			//�N�I���e�B�A�b�v����?
			m_Move *= ENEMY_ATTENUATION;
			m_Pos += m_Move;
		}
		else if (m_CntFrame < m_FrameDest)
		{
			//�u���[�L�̎�G��
			m_Pos = Easing::EaseValue((float)m_CntFrame / m_FrameDest, m_Start,
				m_PosDest, EaseType::OutCubic);

		}

		//�g��Ək���̌J��Ԃ�
		if (m_Expansion)
		{
			m_Scl = Easing::EaseValue(m_SclTime, CHANGE_SCL_MIN,
				CHANGE_SCL_MAX, EaseType::Linear);
			m_SclTime += CHANGE_SCL_SPEED;
			if (m_SclTime >= 1.0f)
			{
				m_Expansion = false;
			}
		}
		else
		{
			m_Scl = Easing::EaseValue(m_SclTime, CHANGE_SCL_MIN,
				CHANGE_SCL_MAX, EaseType::Linear);
			m_SclTime -= CHANGE_SCL_SPEED;
			if (m_SclTime <= 0.0f)
			{
				m_Expansion = true;
			}

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
	m_WaitTime = waitTime;
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
	collider->RegisterToCheckList(BoxCollider3DTag::SnakeEnemy);
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
	m_WaitTime = 0;
	m_CurrentIndex = 0;
	m_PosDestMax = 0;
	m_FramePassed = 0;
	m_WaitCount = 0;

	m_Active = false;

	m_Pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_Dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_RotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	m_FrameDest = 0;
	m_Dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_PosDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_CntFrame = 0;

	m_Start = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_FrameDest = 0.0f;

	m_RotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_CntFrame = 0.0f;

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
	//�X�V�O��m_CurrentIndex��ۑ�
	m_PrevIndex = m_CurrentIndex;


	//�Ō�̓_�̃t���[��
	int last = m_FramePassed + m_FrameDestList[m_PosDestMax - 2];

	if (m_Active)
	{
		if (m_CntFrame == last && m_CurrentIndex == m_PosDestMax - 2)
		{
			//���̂܂ܐi��
			m_Move = (m_PosDestList[m_PosDestMax - 1] - m_PosDestList[m_PosDestMax - 2]) / ENEMY_FRAME_SNAKE;

		}
		else if (m_CntFrame >= last && m_CurrentIndex == m_PosDestMax - 2)
		{
			//�������I�������
			if (m_CntFrame >= last + ENEMY_FALSE_SNAKE)
			{
				m_Active = false;
			}
			m_Pos += m_Move;
		}//��~
		else if ((m_CntFrame > (m_FramePassed + m_FrameDestList[m_CurrentIndex])) && m_CurrentIndex <= m_PosDestMax - 2)
		{
			//��~���̃t���[�����ꎞ�ۑ�����
			m_WaitCount++;
			//��~�̎��Ԃ��߂�����
			if (m_WaitCount == m_WaitTime)
			{
				//��~�̎��Ԃ��J�E���^�[�ɓ����
				m_FramePassed = m_CntFrame;
				m_WaitCount = 0;
			}
		}//���̓_�ɒ�������
		else if ((m_CntFrame == (m_FramePassed + m_FrameDestList[m_CurrentIndex])) && m_CurrentIndex <= m_PosDestMax - 2)
		{
			//index�����̓_�Ɏw��
			m_CurrentIndex++;
			//���܂ł̏��v���Ԃ��L�^
			m_FramePassed = m_CntFrame;
		}
		else if (m_CurrentIndex <= m_PosDestMax - 2)
		{
			m_Pos = Easing::EaseValue((float(m_CntFrame - m_FramePassed) / m_FrameDestList[m_CurrentIndex]),
				m_PosDestList[m_CurrentIndex], m_PosDestList[m_CurrentIndex + 1], EaseType::OutCubic);
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

		BoxCollider3D::DrawCollider(collider);
	}
}

/****************************************
�Z�b�g����
*****************************************/
void EnemySnake::VSet(D3DXVECTOR3 start, D3DXVECTOR3 end1, int frame)
{
	//��
}

void EnemySnake::Set(vector<D3DXVECTOR3> posDestList, vector<int> frameDestList, int waitTime)
{
	m_PosDestList = posDestList;
	m_FrameDestList = frameDestList;
	m_WaitTime = waitTime;

	m_PosDestMax = m_PosDestList.size();

	m_Active = true;
}