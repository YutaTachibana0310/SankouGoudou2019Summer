//=====================================
//
//�v���C���[����[player.cpp]
//Author:GP12B332 12 ����
//
//=====================================
#include "player.h"

#include "main.h"
#include "player.h"
#include "PlayerController.h"
#include "GameParticleManager.h"

#include "starUI.h"
#include "debugWindow.h"

using namespace std;

/**************************************
�}�N����`
***************************************/
#define PLAYER_MODEL  "data/MODEL/airplane000.x"

/**************************************
�\���̒�`
***************************************/


/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�v���g�^�C�v�錾
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
Player::Player()
{
	mesh = new MeshContainer();
	
	mesh->Load(PLAYER_MODEL);
}

/**************************************
�f�X�g���N�^
***************************************/
Player::~Player()
{
	SAFE_DELETE(mesh);
}

/*************************************
����������
**************************************/
void Player::Init()
{
	transform.pos = PLAYER_CENTER;
	transform.scale = D3DXVECTOR3(2.0f, 2.0f, 2.0f);
	transform.rot = D3DXVECTOR3(0.0f, D3DXToRadian(180.0f), 0.0f);
	active = true;

	GameParticleManager::Instance()->SetPlayerTrailParticle(&transform.pos, &active);
	return;
}

/***************************************
�I������
****************************************/
void Player::Uninit()
{
	active = false;
}

/****************************************
�X�V����
*****************************************/
int Player::Update()
{
	if (!active)
		return STATE_CONTINUOUS;

	int stateResult = STATE_CONTINUOUS;

	if (state != NULL)
		stateResult = state->OnUpdate(this);

	return stateResult;
}

/*****************************************
�`�揈��
******************************************/
void Player::Draw()
{
	if (!active)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, quatMatrixs, shadowMatrix, mtxWorld;
	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, transform.scale.y, transform.scale.x, transform.scale.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, transform.rot.y, transform.rot.x, transform.rot.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, transform.pos.x, transform.pos.y, transform.pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	mesh->Draw();
}

/*****************************************
��ԑJ��
******************************************/
void Player::ChangeState(IStateMachine<Player> *next)
{
	state = next;
	state->OnStart(this);
}