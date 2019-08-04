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
#include "PostEffect\SpikeNoiseController.h"

using namespace std;

/**************************************
�}�N����`
***************************************/
#define PLAYER_MODEL				"data/MODEL/airplane000.x"
#define PLAYER_DAMAGE				(10.0f)		//�v���C���[��1��̔�e�Ŏ󂯂�_���[�W
#define PLAYER_INVINCIBLE_DURATION	(30000)		//�v���C���[�̖��G����

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

	collider = new TrailCollider(TrailColliderTag::Player);
	collider->active = false;
	collider->SetAddressZ(&transform.pos.z);
	collider->AddObserver(this);
}

/**************************************
�f�X�g���N�^
***************************************/
Player::~Player()
{
	SAFE_DELETE(mesh);
	SAFE_DELETE(collider);
}

/*************************************
����������
**************************************/
void Player::Init()
{
	transform.pos = PLAYER_CENTER;
	transform.scale = D3DXVECTOR3(2.0f, 2.0f, 2.0f);
	active = true;

	GameParticleManager::Instance()->SetPlayerTrailParticle(&transform.pos, &active);

	cntInvincible = PLAYER_INVINCIBLE_DURATION;

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

	//���G���Ԃ̍X�V
	if (!flgInvincible)
	{
		cntInvincible--;
		if (cntInvincible == 0)
			collider->active = false;
	}

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
	
	transform.SetWorld();
	mesh->Draw();

	TrailCollider::DrawCollider(collider);
}

/*****************************************
��ԑJ��
******************************************/
void Player::ChangeState(IStateMachine<Player> *next)
{
	state = next;
	state->OnStart(this);
}

/*****************************************
�Փ˔���ʒm����
******************************************/
void Player::OnNotified(ObserveSubject* notifier)
{
	SpikeNoiseController::Instance()->SetNoise(0.5f, 20);
	hp -= PLAYER_DAMAGE;

	//���G���ԊJ�n
	cntInvincible = PLAYER_INVINCIBLE_DURATION;
	collider->active = false;
	flgInvincible = true;
}