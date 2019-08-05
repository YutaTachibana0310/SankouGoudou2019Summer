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
#define PLAYER_MODEL				"data/MODEL/player.x"
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
	//�A�j���[�V����������
	animation = new AnimContainer();
	animation->LoadXFile(PLAYER_MODEL, "Player");
	animation->SetupCallbackKeyFrames("Flying");
	animation->SetupCallbackKeyFrames("Attack");
	animation->SetupCallbackKeyFrames("FireBomber");
	animation->LoadAnimation("Flying", PlayerAnimID::Flying);
	animation->LoadAnimation("Attack", PlayerAnimID::Attack);
	animation->LoadAnimation("FireBomber", PlayerAnimID::FireBomber);
	animation->SetShiftTime(PlayerAnimID::Flying, 0.2f);
	animation->SetShiftTime(PlayerAnimID::Attack, 0.2f);
	animation->SetShiftTime(PlayerAnimID::FireBomber, 0.2f);

	collider = new TrailCollider(TrailColliderTag::Player);
	collider->active = false;
	collider->SetAddressZ(&transform.pos.z);
	collider->AddObserver(this);

	animation->ChangeAnim(PlayerAnimID::Flying, 1.5f, true);
}

/**************************************
�f�X�g���N�^
***************************************/
Player::~Player()
{
	SAFE_DELETE(animation);
	SAFE_DELETE(collider);
}

/*************************************
����������
**************************************/
void Player::Init()
{
	transform.pos = PLAYER_CENTER;
	transform.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
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

	//�A�j���[�V�����̍X�V
	animation->Update(1.0f / 60.0f);

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
	D3DXMATRIX mtxWorld = transform.GetMatrix();
	D3DMATERIAL9 matDef;

	pDevice->GetMaterial(&matDef);
	
	transform.SetWorld();
	animation->Draw(&mtxWorld);

	pDevice->SetMaterial(&matDef);

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

/*****************************************
�A�j���[�V�����؂�ւ�����
******************************************/
void Player::ChangeAnim(PlayerAnimID next)
{
	static const float shitTime[PlayerAnimID::PlayerAnimMax] = {
		1.5f,
		7.0f,
		1.0f
	};

	animation->ChangeAnim(next, shitTime[next], true);
}