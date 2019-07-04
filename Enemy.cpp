//=====================================
//
//�G�̏��� [Enemy.cpp]
//
//Author:�n�@�O��
//=====================================
#include "Enemy.h"

#include "debugWindow.h"

#include  <math.h>


/**************************************
�}�N����`
***************************************/
//#define ENEMY_NUM (4) //1�O���[�v�̃L���[�u(�G�l�~�[)�̗�
#define ENEMY_MODEL  "data/MODEL/airplane000.x"

#define ENEMY_FALSE (300)	//false�̎���(�������ς����Ă���)

/****************************************
static�ϐ�
****************************************/
MeshContainer* Enemy::mesh;
UINT Enemy::instanceCount;

/****************************************
�R���X�g���N�^
****************************************/
Enemy::Enemy()
{
	instanceCount++;
	if (mesh == NULL)
	{
		mesh = new MeshContainer();
		mesh->Load(ENEMY_MODEL);
	}
}

/****************************************
�f�X�g���N�^
****************************************/
Enemy::~Enemy()
{
	instanceCount--;
	if (instanceCount == 0)
	{
		SAFE_DELETE(mesh);
	}
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
HRESULT  EnemyStraight::Init(void)
{
	active = false;
	

	pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scl = D3DXVECTOR3(2.0f, 2.0f, 2.0f);
	rot = D3DXVECTOR3(0.0f, 59.7f, 0.0f);
	rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	

	frameDest = 0;
	dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	posDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	cntFrame = 0;
	return S_OK;
}
/****************************************
�I������
*****************************************/
void EnemyStraight::Uninit(void)
{
	
	
}
/****************************************
�X�V����
*****************************************/
void EnemyStraight::Update(void)
{
	if (active)	
	{
		if (cntFrame < frameDest)
		{
			pos += move;
		}

		//count����.
		cntFrame++;
	}
	BeginDebugWindow("posEnemyStraight");
	DebugText("POS:%f,%f,%f",pos.x,pos.y,pos.z);
	DebugText("MOVE:%f,%f,%f", move.x, move.y, move.z);
	EndDebugWindow("pos");
}

/****************************************
�`�揈��
*****************************************/
void EnemyStraight::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;
	
	if (active)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&mtxWorld);

		// �X�P�[���𔽉f
		D3DXMatrixScaling(&mtxScl, scl.y, scl.x, scl.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTranslate, pos.x, pos.y, pos.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

		mesh->Draw();
	}
				
}
/****************************************
�Z�b�g����
*****************************************/

void EnemyStraight::Set(D3DXVECTOR3 start, D3DXVECTOR3 end,int frame)
{
		
	frameDest = frame;
	posDest = end;
	pos = start;
	dir = end - start;
	move = dir / frame;

	active = true;
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
HRESULT EnemyChange::Init(void)
{
	active = false;
	

	pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scl = D3DXVECTOR3(2.0f, 2.0f, 2.0f);
	rot = D3DXVECTOR3(0.0f, 59.7f, 0.0f);
	rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	cntFrame = 0;

	frameDest = 0;
	dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	posDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	return S_OK;
}
/****************************************
�I������
*****************************************/
void EnemyChange::Uninit()
{
	
	
}
/****************************************
�X�V����
*****************************************/
void EnemyChange::Update()
{
	if (active)
	{

		if (cntFrame > frameDest + m_waitTime + ENEMY_FALSE)
		{
			active = false;
		}

		if (cntFrame > frameDest && cntFrame <= frameDest + m_waitTime)
		{
			
		}
		else if (cntFrame > frameDest +m_waitTime)
		{
		
			move = vecChange;
			pos += move;
		}
		else if (cntFrame < frameDest)
		{
			pos += move;

		}
		//count����
		cntFrame++;
	}

	BeginDebugWindow("posEnemyChange");
	DebugText("POS:%f,%f,%f", pos.x, pos.y, pos.z);
	DebugText("MOVE:%f,%f,%f", move.x, move.y, move.z);
	DebugText("ACTIVE:%d", active);
	EndDebugWindow("pos");
	
}
/****************************************
�`�揈��
*****************************************/
void EnemyChange::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;

	if (active)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&mtxWorld);

		// �X�P�[���𔽉f
		D3DXMatrixScaling(&mtxScl, scl.y, scl.x, scl.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTranslate, pos.x, pos.y, pos.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

		mesh->Draw();
	}
}

/****************************************
�Z�b�g����
*****************************************/
void EnemyChange::Set(D3DXVECTOR3 start, D3DXVECTOR3 end, int frame)
{
	//��
}

void EnemyChange::SetVec(D3DXVECTOR3 start, D3DXVECTOR3 end, int frame,  int waitTime,D3DXVECTOR3 vec)
{
	vecChange = vec;
	m_waitTime = waitTime;
	frameDest = frame;
	posDest = end;
	pos = start;
	dir = end - start;
	move = dir / frame;

	active = true;
}

