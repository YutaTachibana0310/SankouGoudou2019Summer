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
#include "PlayerBomber.h"

using namespace std;
/**************************************
�}�N����`(�����K��:�傫����)
***************************************/
#define ENEMY_COLLIDER_SIZE	(D3DXVECTOR3(10.0f, 10.0f, 10.0f))
#define CHANGE_FALSE	(300)				//false�̎���(�������ς����Ă���)
#define SNAKE_FALSE		(900)

#define	ENEMY_ATTENUATION	(0.98f)				//�����W�� 

#define SNAKE_FRAME	(200)

//#define GET_RANDOM(a, b)		((a) + rand() / (RAND_MAX / ((b) - (a) + 1) + 1))

#define STRAIGHT_SCL_MIN	(D3DXVECTOR3(0.0f, 0.0f, 0.0f))  //�X�P�[���̃A�j���[�V�����̍ő�l	
#define STRAIGHT_SCL_SPEED	(0.01f)							 //�A�j���[�V�����̎��Ԃ̑���

#define CHANGE_SCL_MAX		(D3DXVECTOR3(1.0f, 1.0f, 1.0f))
#define CHANGE_SCL_MIN		(D3DXVECTOR3(0.8f, 0.8f, 0.8f))
//#define CHANGE_SCL_SPEED	(0.05f)
#define SNAKE_SCL_MAX		(D3DXVECTOR3(1.0f, 1.0f, 1.0f))
#define SNAKE_SCL_MIN		(D3DXVECTOR3(0.8f, 0.8f, 0.8f))
//#define SNAKE_SCL_SPEED	(0.05f)
#define SCL_MAX				(D3DXVECTOR3(1.0f, 1.0f, 1.0f))
#define SCL_MIN				(D3DXVECTOR3(0.8f, 0.8f, 0.8f))

#define STRAIGHT_WAIT_TIME			(0.9)				//�T���v�����O����

#define MIDIUM_ANIMATION_TIME		(3)					//�_�Ŏ���

/****************************************
static�ϐ�
****************************************/
UINT Enemy::m_InstanceCount;

/****************************************
�R���X�g���N�^
****************************************/
Enemy::Enemy() : 
	m_FlgDestroyed(false)
{
	m_InstanceCount++;
	ResourceManager::Instance()->GetMesh("Enemy", m_pMesh);

	m_Collider = new BoxCollider3D(BoxCollider3DTag::Enemy, &m_Pos);
	m_Collider->SetSize(ENEMY_COLLIDER_SIZE);
	m_Collider->active = true;
	m_Collider->AddObserver(this);
}

/****************************************
�f�X�g���N�^
****************************************/
Enemy::~Enemy()
{
	m_InstanceCount--;
	SAFE_DELETE(m_Collider);
}

/****************************************
�Փ˔���ʒm���V�[�o�[
****************************************/
void Enemy::OnNotified(BoxCollider3DTag other)
{
	m_FlgDestroyed = true;
	m_Active = false;
}

/****************************************
�{���o�[���e�R�[���o�b�N
****************************************/
void Enemy::OnHitBomber()
{
	m_FlgDestroyed = true;
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
�g��Ək���̃A�j���[�V����
****************************************/
int	Enemy::Animation()
{
	//�A�j���[�V�����𓮂�����
	if (!m_AnimationActive)
		return 0;

	if (m_Expansion)
	{
		m_Scl = Easing::EaseValue(m_SclRate,SCL_MIN,
			SCL_MAX, EaseType::Linear);
		m_SclRate += m_SclSpeed;
		if (m_SclRate >= 1.0f)
		{
			m_Expansion = false;
		}
	}
	else
	{
		m_Scl = Easing::EaseValue(m_SclRate, SCL_MIN,
			SCL_MAX, EaseType::Linear);
		m_SclRate -= m_SclSpeed;
		if (m_SclRate <= 0.0f)
		{
			m_Expansion = true;
		}

	}

	return 1;
}

//0903
void Enemy::SetAnimation(bool active,bool expansion, float sclRate,float speed)
{
	m_AnimationActive = active;
	m_Expansion = expansion;
	m_SclRate = sclRate;
	m_SclSpeed = speed;
}

/****************************************
����������
****************************************/
HRESULT  EnemyStraight::VInit(void)
{
	m_PositionHistoryTimer = 0.0f;
	m_PositionHistoryIndex = 0;

	for (int i = 0; i < SHADOW_MAX; i++)
	{
		m_ShadowPos[i] = D3DXVECTOR3(500.0f, 0.0f, 0.0f);
		m_ShadowScl[i] = m_Scl;

	}

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

	m_AnimationActive = false;
	m_Expansion = true;
	m_SclRate = 0.0f;
	m_SclSpeed = 0.0f;
	
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
			m_Pos = Easing::EaseValue(m_CntFrame / m_FrameDest, m_Start,
				m_PosDest, EaseType::InSine);
			
		}
		else
		{
			m_Active = false;
		}

		//�A�j���[�V�����̏���
		if (!m_AnimationActive)
		{
			//����鎞�̊g��
			if(m_SclRate < 1.0f)
			{
				m_Scl = Easing::EaseValue(m_SclRate, STRAIGHT_SCL_MIN,
					D3DXVECTOR3(1.0f, 1.0f, 1.0f), EaseType::OutCubic);
				m_SclRate += STRAIGHT_SCL_SPEED;

				//���Ԃ���C��1.0�𒴂����ꍇ
				if (m_SclRate >= 1.0f)
				{
					m_Scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
					//���̃A�j���[�V�������n�߂�
					SetAnimation(true, false, 1.0f, 0.05f);
				}
			}
		}
		else
		{
			Animation();
		}
		
	}

	if (m_CntFrame > m_PositionHistoryTimer + STRAIGHT_WAIT_TIME)
	{
		m_PositionHistoryTimer = m_CntFrame;
		m_PositionHistoryIndex++;

		if (m_PositionHistoryIndex > SHADOW_MAX - 1)
		{
			m_PositionHistoryIndex = SHADOW_MAX - 1;
			//�L���[����
			for (int i = 1; i < SHADOW_MAX; i++)
			{
				m_ShadowPos[i - 1] = m_ShadowPos[i];
				m_ShadowScl[i - 1] = m_ShadowScl[i];
			}
				
		}
		m_ShadowPos[m_PositionHistoryIndex] = m_Pos;
		m_ShadowScl[m_PositionHistoryIndex] = m_Scl;
	}

	//�Ō��count����. 
	m_CntFrame++;
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
		
	}
	m_pMesh->SetMaterialAlpha(1.0f);
}
/****************************************
�Z�b�g����
*****************************************/
void EnemyStraight::VSet(D3DXVECTOR3 start, D3DXVECTOR3 end, float frame)
{

	m_FrameDest = frame;
	m_PosDest = end;
	//?
	m_Start = m_Pos = start;
	//m_CntFrame = 0;

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

	m_Active = false;

	m_Scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);

	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_PosDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Start = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_FrameDest = 0.0f;

	m_RotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_CntFrame = 0.0f;

	m_SclRate = 0.0f;
	m_Expansion = true;
	m_AnimationActive = false;
	m_SclSpeed = 0.0f;

	SetAnimation(true,true, 0.0f,0.05f);
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

		if (m_CntFrame > m_FrameDest + m_WaitTime + CHANGE_FALSE)
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
			m_Pos = Easing::EaseValue(m_CntFrame / m_FrameDest, m_Start,
				m_PosDest, EaseType::OutCubic);

		}

		Animation();
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
void EnemyChange::VSet(D3DXVECTOR3 start, D3DXVECTOR3 end, float frame)
{
	//��
}

void EnemyChange::VSetVec(D3DXVECTOR3 start, D3DXVECTOR3 end, float frame, float waitTime, D3DXVECTOR3 vec)
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
	m_Collider->RegisterToCheckList(BoxCollider3DTag::SnakeEnemy);
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
	m_WaitTime = 0.0f;
	m_CurrentIndex = 0;
	m_PosDestMax = 0;
	m_FramePassed = 0.0f;
	m_WaitCount = 0.0f;

	m_Active = false;

	m_Scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_PosDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Start = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_FrameDest = 0.0f;

	m_RotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_CntFrame = 0.0f;

	m_AnimationActive = false;
	m_Expansion = true;
	m_SclRate = 0.0f;
	m_SclSpeed = 0.0f;

	SetAnimation(true, true, 0.0f, 0.05f);
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
	float last = m_FramePassed + m_FrameDestList[m_PosDestMax - 2];

	if (m_Active)
	{
		if (m_CntFrame == last && m_CurrentIndex == m_PosDestMax - 2)
		{
			//���̂܂ܐi��
			m_Move = (m_PosDestList[m_PosDestMax - 1] - m_PosDestList[m_PosDestMax - 2]) / SNAKE_FRAME;

		}
		else if (m_CntFrame >= last && m_CurrentIndex == m_PosDestMax - 2)
		{
			//�������I�������
			if (m_CntFrame >= last + SNAKE_FALSE)
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
				m_WaitCount = 0.0f;
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

		Animation();
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

		BoxCollider3D::DrawCollider(m_Collider);
	}
}

/****************************************
�Z�b�g����
*****************************************/
void EnemySnake::VSet(D3DXVECTOR3 start, D3DXVECTOR3 end1, float frame)
{
	//��
}

void EnemySnake::Set(vector<D3DXVECTOR3> posDestList, vector<float> frameDestList, float waitTime)
{
	m_PosDestList = posDestList;
	m_FrameDestList = frameDestList;
	m_WaitTime = waitTime;

	m_PosDestMax = m_PosDestList.size();

	m_Active = true;
}


//EnemyMidium
/****************************************
�R���X�g���N�^
****************************************/
EnemyMidium::EnemyMidium()
{
	ResourceManager::Instance()->GetMesh("MidiumEnemy", m_pMesh);
}

/****************************************
�f�X�g���N�^
****************************************/
EnemyMidium ::~EnemyMidium()
{

}

/****************************************
����������
****************************************/
HRESULT EnemyMidium::VInit()
{
	m_CntFrameNow = 0.0f;
	m_Visible = true;
	m_CntAnim = 0;

	m_Active = false;

	m_Scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_PosDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Start = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_FrameDest = 0.0f;

	m_RotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_CntFrame = 0.0f;

	m_SclRate = 0.0f;
	m_Expansion = true;
	m_AnimationActive = false;
	m_SclSpeed = 0.0f;

	return S_OK;
}

/****************************************
�I������
*****************************************/
void EnemyMidium::VUninit()
{
	m_Active = false;
}

/****************************************
�X�V����
*****************************************/
void EnemyMidium::VUpdate()
{
	if (m_Active)
	{

		m_Pos = Easing::EaseValue(m_CntFrameNow / m_FrameDest, m_Start,
			m_PosDest, EaseType::OutCubic);

		//count����
		m_CntFrameNow++;
		m_CntFrame++;


	}
}

/****************************************
�`�揈��
*****************************************/
void EnemyMidium::VDraw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;

	//�A�N�e�B�u&&������
	if (m_Active&&m_Visible)
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
Move����(�����邽�тɌĂяo��)
*****************************************/
void EnemyMidium::Move(D3DXVECTOR3 posDest, float frameDest)
{
	m_PosDest = posDest;
	m_FrameDest = frameDest;
	m_Start = m_Pos;
	//���̃��C���Ɉړ����邽�тɁAm_CntFrameNow��0�ɖ߂�
	m_CntFrameNow = 0.0f;

}

/****************************************
�Z�b�g����(�ŏ��̐ݒ�)
*****************************************/
void EnemyMidium::Set(D3DXVECTOR3 start)
{
	m_Start = start;
	m_Active = true;
}

/****************************************
��e�A�j���[�V��������
*****************************************/
void EnemyMidium::HitAnimation()
{
	m_CntAnim++;
	if ((m_CntAnim % MIDIUM_ANIMATION_TIME) == 0)
	{
		m_Visible = false;
	}
	else
	{
		m_Visible = true;
	}
	

}

/****************************************
����
*****************************************/
void EnemyMidium::SetHitAnimation()
{
	m_CntAnim = 0;
}

/****************************************
�Z�b�g����
*****************************************/
void EnemyMidium::VSet(D3DXVECTOR3 start, D3DXVECTOR3 end, float frame)
{
	//��
}