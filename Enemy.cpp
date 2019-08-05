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
//#define ENEMY_MODEL  "data/MODEL/airplane000.x"

#define ENEMY_FALSE_CHANGE (300)				//false�̎���(�������ς����Ă���)
#define ENEMY_FALSE_SNAKE	(900)

#define	ENEMY_ATTENUATION (0.98f)				//�����W�� 

#define ENEMY_FRAME_SNAKE (200)

//#define GET_RANDOM(a, b)		((a) + rand() / (RAND_MAX / ((b) - (a) + 1) + 1))

#define STRAIGHT_SCL_MIN (D3DXVECTOR3(0.0f, 0.0f, 0.0f))  //�X�P�[���̃A�j���[�V�����̍ő�l	
#define STRAIGHT_SCL_SPEED (0.01f)						  //�A�j���[�V�����̎��Ԃ̑���

#define CHANGE_SCL_MAX (D3DXVECTOR3(1.0f, 1.0f, 1.0f))
#define CHANGE_SCL_MIN (D3DXVECTOR3(0.8f, 0.8f, 0.8f))
#define CHANGE_SCL_SPEED (0.05f)

#define WAIT_TIME       (0.9)							  //�T���v�����O����

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
		m_ShadowPos[i] = D3DXVECTOR3(500.0f, 0.0f, 0.0f);// m_Pos;// D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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
			//if (f < 1.0f)
			{
				m_Scl = Easing::EaseValue(m_SclTime, STRAIGHT_SCL_MIN,
					D3DXVECTOR3(1.0f, 1.0f, 1.0f), EaseType::OutCubic);

				m_SclTime += STRAIGHT_SCL_SPEED;

				//if (f >= 1.0f)
				//{
				//	m_Scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
				//}
			}

		}
		else
		{
			//m_Active = false;
		}

		//count����.
		m_CntFrame++;
	}


	//shadow
	//for (int i = 0; i < SHADOW_MAX; i++)
	//{
		//m_ShadowPos[i] = m_Pos;
	//}
	if (m_CntFrame > position_history_timer + WAIT_TIME)
	{

		position_history_timer = m_CntFrame;
		position_history_index++;

		if (position_history_index > SHADOW_MAX - 1)
		{
			position_history_index = SHADOW_MAX - 1;
			//�L���[����
			for (int i = 1; i < SHADOW_MAX; i++)
				m_ShadowPos[i - 1] = m_ShadowPos[i];
		}
		m_ShadowPos[position_history_index] = m_Pos;

	}

#if 0
	BeginDebugWindow("scl");
	DebugText("%f,%f,%f", m_Scl.x, m_Scl.y, m_Scl.z);
	DebugText("%f", m_SclTime);
	EndDebugWindow("scl");
#endif
}

/****************************************
�`�揈��
*****************************************/
void EnemyStraight::VDraw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;

	//0803
	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	//pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

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

		//for (DWORD i = 0; i < m_pMesh->GetMaterialNum(); i++)
		//{
		//	D3DMATERIAL9 a;
		//	m_pMesh->GetMaterial(i, &a);
		//	a.Diffuse.a = 0.0f;
		//	//m_pMesh->materials[i].Diffuse.a = 0.0f;
		//	//pDevice->SetMaterial(&m_pMesh->materials[i]);
		//	

		//}
		//m_pMesh->SetMaterialAlpha(0.0f);
		//m_pMesh->SetMaterialAlpha(0.0f);

		//m_pMesh->SetMaterialColor(D3DCOLOR_RGBA(0, 240, 240, 256));

		m_pMesh->Draw();
		//m_pMesh->SetMaterialAlpha(1.0f);


	}


	for (int n = 0; n < SHADOW_MAX; n++)
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&mtxWorld);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTranslate, m_ShadowPos[n].x, m_ShadowPos[n].y, m_ShadowPos[n].z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

		//m_pMesh->SetMaterialColor(D3DCOLOR_RGBA(0, 240, 240, 20 + n * 10));
		m_pMesh->SetMaterialAlpha(float(0.07 + n * 0.039));
		m_pMesh->Draw();

		m_pMesh->SetMaterialAlpha(1.0f);
		//BeginDebugWindow("pos");
		//DebugText("%f,%f,%f", m_ShadowPos[n].x, m_ShadowPos[n].y, m_ShadowPos[n].z);
		//EndDebugWindow("pos");
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
	g_mode = MODE_EXPANSION;

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
		switch (g_mode)
		{
		case MODE_EXPANSION:
			m_Scl = Easing::EaseValue(m_SclTime, CHANGE_SCL_MIN,
				CHANGE_SCL_MAX, EaseType::Linear);
			m_SclTime += CHANGE_SCL_SPEED;
			if (m_SclTime >= 1.0f)
			{
				g_mode = MODE_SHRINK;
			}
			break;

		case  MODE_SHRINK:
			m_Scl = Easing::EaseValue(m_SclTime, CHANGE_SCL_MIN,
				CHANGE_SCL_MAX, EaseType::Linear);
			m_SclTime -= CHANGE_SCL_SPEED;
			if (m_SclTime <= 0.0f)
			{
				g_mode = MODE_EXPANSION;
			}
			break;

		}
		//count����
		m_CntFrame++;

		//BeginDebugWindow("scl");
		//DebugText("%f,%f,%f", m_Scl.x, m_Scl.y, m_Scl.z);
		//DebugText("%f", m_SclTime);
		//EndDebugWindow("scl");
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
	m_posDestMax = 0;
	m_framePassed = 0;
	m_waitcount = 0;

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
	int last = m_framePassed + m_FrameDestList[m_posDestMax - 2];

	if (m_Active)
	{
		if (m_CntFrame == last && m_CurrentIndex == m_posDestMax - 2)
		{
			//���̂܂ܐi��
			m_Move = (m_PosDestList[m_posDestMax - 1] - m_PosDestList[m_posDestMax - 2]) / ENEMY_FRAME_SNAKE;

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
		else if ((m_CntFrame > (m_framePassed + m_FrameDestList[m_CurrentIndex])) && m_CurrentIndex <= m_posDestMax - 2)
		{
			//��~���̃t���[�����ꎞ�ۑ�����
			m_waitcount++;
			//��~�̎��Ԃ��߂�����
			if (m_waitcount == m_WaitTime)
			{
				//��~�̎��Ԃ��J�E���^�[�ɓ����
				m_framePassed = m_CntFrame;
				m_waitcount = 0;
			}
		}//���̓_�ɒ�������
		else if ((m_CntFrame == (m_framePassed + m_FrameDestList[m_CurrentIndex])) && m_CurrentIndex <= m_posDestMax - 2)
		{
			//index�����̓_�Ɏw��
			m_CurrentIndex++;
			//���܂ł̏��v���Ԃ��L�^
			m_framePassed = m_CntFrame;
		}
		else if (m_CurrentIndex <= m_posDestMax - 2)
		{
			m_Pos = Easing::EaseValue((float(m_CntFrame - m_framePassed) / m_FrameDestList[m_CurrentIndex]),
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

	m_posDestMax = m_PosDestList.size();

	m_Active = true;
}