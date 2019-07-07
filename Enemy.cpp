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



/**************************************
�}�N����`
***************************************/
//#define ENEMY_NUM (4) //1�O���[�v�̃L���[�u(�G�l�~�[)�̗�
#define ENEMY_MODEL  "data/MODEL/airplane000.x"

#define ENEMY_FALSE (300)				//false�̎���(�������ς����Ă���)

#define	ENEMY_ATTENUATION (0.98f)		//�����W�� 

//Enemy
/****************************************
�R���X�g���N�^
****************************************/
Enemy::Enemy()
{

}

/****************************************
�f�X�g���N�^
****************************************/
Enemy::~Enemy()
{

}

//EnemyStraight
/****************************************
�R���X�g���N�^
****************************************/
EnemyStraight::EnemyStraight()
{
	meshPlayer = new MeshContainer();
	meshPlayer->Load(ENEMY_MODEL);
}

/****************************************
�f�X�g���N�^
****************************************/
EnemyStraight::~EnemyStraight()
{

	SAFE_DELETE(meshPlayer);
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
	
	m_start =  D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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
		if (cntFrame <= frameDest )
		{
			//�u���[�L�̎�G��
			pos = Easing<D3DXVECTOR3>::GetEasingValue(((float)cntFrame/(float)frameDest), &m_start, 
				&posDest, EasingType::OutCubic);
			//pos += move;
		}

		//if (cntFrame < frameDest-20)
		//{
		//	

		//	pos += move;
		//}
		//else if (cntFrame >= frameDest - 20 && cntFrame <= frameDest )
		//{
		//	//// �ړ��ʂɊ�����������
		//	//move.x = (0.0f + move.x) * RATE_MOVE_PLAYER;
		//	////move.x *= RATE_MOVE_PLAYER;
		//	//move.y = (0.0f + move.z) * RATE_MOVE_PLAYER;
		//	//move.z = (0.0f + move.z) * RATE_MOVE_PLAYER;
		//	pos += move;
		//}

		//count����.
		cntFrame++;
	}
	BeginDebugWindow("posEnemyStraight");
	DebugText("cntFrame:%d", cntFrame);
	DebugText("POS:%f,%f,%f", pos.x, pos.y, pos.z);
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

		meshPlayer->Draw();
	}

}
/****************************************
�Z�b�g����
*****************************************/

void EnemyStraight::Set(D3DXVECTOR3 start, D3DXVECTOR3 end, int frame)
{

	frameDest = frame;
	posDest = end;
	//pos = start;
	m_start = start;
	//dir = end - start;
	//move = dir / frame;

	active = true;
}




//EnemyChange
/****************************************
�R���X�g���N�^
****************************************/
EnemyChange::EnemyChange()
{
	meshPlayer = new MeshContainer();
	meshPlayer->Load(ENEMY_MODEL);
}
/****************************************
�f�X�g���N�^
****************************************/
EnemyChange::~EnemyChange()
{
	SAFE_DELETE(meshPlayer);

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

	m_start = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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

		if (cntFrame > frameDest && cntFrame < frameDest + m_waitTime)
		{

		}
		else if (cntFrame == frameDest + m_waitTime)
		{
			move = vecChange;
			
		}
		else if (cntFrame > frameDest + m_waitTime)
		{

			//move = vecChange;

			//�N�I���e�B�A�b�v����?
			move *= ENEMY_ATTENUATION;
			pos += move;
		}
		else if (cntFrame < frameDest)
		{
			//�u���[�L�̎�G��
			pos = Easing<D3DXVECTOR3>::GetEasingValue(((float)cntFrame / (float)frameDest), &m_start,
				&posDest, EasingType::OutCubic);
			//pos += move;
		}
		//count����
		cntFrame++;
	}

	BeginDebugWindow("posEnemyChange");
	DebugText("cntFrame:%d", cntFrame);
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

		meshPlayer->Draw();
	}
}

/****************************************
�Z�b�g����
*****************************************/
void EnemyChange::Set(D3DXVECTOR3 start, D3DXVECTOR3 end, int frame)
{
	//��
}

void EnemyChange::SetVec(D3DXVECTOR3 start, D3DXVECTOR3 end, int frame, int waitTime, D3DXVECTOR3 vec)
{
	vecChange = vec;
	m_waitTime = waitTime;
	frameDest = frame;
	posDest = end;
	//pos = start;
	m_start = start;
	//dir = end - start;
	//move = dir / frame;

	active = true;
}

