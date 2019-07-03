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



//Enemy
/****************************************
�R���X�g���N�^
****************************************/
//Enemy::Enemy()
//{
//
//}

/****************************************
�f�X�g���N�^
****************************************/
//Enemy::~Enemy()
//{
//
//}

//EnemyStraight
/****************************************
�R���X�g���N�^
****************************************/
EnemyStraight::EnemyStraight()
{
	//�������̃R�[�h�̓R���X�g���N�^�ɓ����H
}

/****************************************
�f�X�g���N�^
****************************************/
EnemyStraight::~EnemyStraight()
{
	//�I�������̃R�[�h�̓f�X�g���N�^�ɓ����H
}

/****************************************
����������
****************************************/
HRESULT  EnemyStraight::Init(void)
{
	bUse = false;
	meshPlayer = new MeshContainer();
	meshPlayer->Load(ENEMY_MODEL);

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
	//SAFE_RELEASE?
	SAFE_DELETE(meshPlayer);
}
/****************************************
�X�V����
*****************************************/
void EnemyStraight::Update(void)
{
	if (bUse)	
	{
		//move.y = -1.0f;
		//pos += move;
		
		//((fabsf(pos.x - posDest.x) < 1e-6f) || (fabsf(pos.y - posDest.y) < 1e-6f) || (fabsf(pos.z - posDest.z) < 1e-6f))
		/*double x = D3DXVec3Length(&D3DXVECTOR3(pos - posDest));
		if (!(x< ( (1e-6f))))
		{
			pos += move;
		}*/

		if (cntFrame < frameDest)
		{
			pos += move;
		}

		//count����.
		cntFrame++;
	}
	BeginDebugWindow("posUpdate");
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
	
	if (bUse)
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

		meshPlayer->Draw();
	}
				
}
/****************************************
�Z�b�g����
*****************************************/

void EnemyStraight::Set(D3DXVECTOR3 start, D3DXVECTOR3 end,int frame)
{
		//if (!bUse)
		//{
			frameDest = frame;
	        posDest = end;
			pos = start;
			dir = end - start;			
			move = dir /frame;

			bUse = true;
			//pos.x += 10.0f;

		//}




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
	bUse = false;
	meshPlayer = new MeshContainer();
	meshPlayer->Load(ENEMY_MODEL);

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
	//SAFE_RELEASE?
	SAFE_DELETE(meshPlayer);
}
/****************************************
�X�V����
*****************************************/
void EnemyChange::Update()
{
	if (bUse)
	{
		if (cntFrame > frameDest && cntFrame <= frameDest + m_waitTime)
		{
			
		}
		else if (cntFrame > frameDest +m_waitTime)
		{
			//move.z = -1.0f;
			move = vecChange;
			pos += move;
		}
		else if (cntFrame < frameDest)
		{
			//move.z = 1.0f;
			
			pos += move;
		}
		BeginDebugWindow("posEnemyChange");
		DebugText("POS:%f,%f,%f", pos.x, pos.y, pos.z);
		DebugText("MOVE:%f,%f,%f", move.x, move.y, move.z);
		EndDebugWindow("pos");
		//count����
		cntFrame++;
	}
	
}
/****************************************
�`�揈��
*****************************************/
void EnemyChange::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;

	if (bUse)
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

		meshPlayer->Draw();
	}
}

/****************************************
�Z�b�g����
*****************************************/
void EnemyChange::Set(D3DXVECTOR3 start, D3DXVECTOR3 end, int frame)
{
	//m_waitTime = waitTime;
	/*frameDest = frame;
	posDest = end;
	pos = start;
	dir = end - start;
	move = dir / frame;

	bUse = true;*/
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

	bUse = true;
}

//void EnemyChange::SetTime(int waitTime)
//{
//	
//	if (bUse)
//	{
//
//		m_waitTime = waitTime;
//	}
//	
//
//}