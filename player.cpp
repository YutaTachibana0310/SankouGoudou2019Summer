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
#include "Framework\BoxCollider3D.h"

#include "starButtonUI.h"
#include "debugWindow.h"
#include "sound.h"

#include "PostEffect\SpikeNoiseController.h"

using namespace std;

/**************************************
�}�N����`
***************************************/
#define PLAYER_MODEL				"data/MODEL/player.x"
#define PLAYER_DAMAGE				(10.0f)		//�v���C���[��1��̔�e�Ŏ󂯂�_���[�W
#define PLAYER_INVINCIBLE_DURATION	(300)		//�v���C���[�̖��G����

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

	//�g���C���R���C�_�[�쐬
	collider = new TrailCollider(TrailColliderTag::Player);
	collider->active = false;
	collider->SetAddressZ(&transform.pos.z);
	collider->AddObserver(this);

	//�{�b�N�X�R���C�_�[�쐬
	const float ColliderSize = 5.0f;
	boxCollider = new BoxCollider3D(BoxCollider3DTag::Player, &transform.pos);
	boxCollider->SetSize(D3DXVECTOR3(ColliderSize, ColliderSize, ColliderSize));
	boxCollider->AddObserver(this);
	boxCollider->active = true;

	//�A�j���[�V�����J��
	animation->ChangeAnim(PlayerAnimID::Flying, 1.5f, true);

	//�X�g�b�N�G�t�F�N�g�쐬
	stockEffect = new BomberStockEffect();
}

/**************************************
�f�X�g���N�^
***************************************/
Player::~Player()
{
	SAFE_DELETE(animation);
	SAFE_DELETE(collider);
	SAFE_DELETE(boxCollider);
	SAFE_DELETE(stockEffect);
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
	if (flgInvincible)
	{
		cntInvincible--;
		if (cntInvincible == 0)
		{
			flgInvincible = false;
			collider->active = true;
		}
	}

	//�{���o�[�X�g�b�N�G�t�F�N�g�̍X�V
	stockEffect->transform.pos = transform.pos;
	stockEffect->Update();

	return stateResult;
}

/****************************************
�A�j���[�V�����̍X�V
*****************************************/
void Player::Animation()
{
	animation->Update(1.0f / 60.0f);
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

	BoxCollider3D::DrawCollider(boxCollider);

	pDevice->SetMaterial(&matDef);

	TrailCollider::DrawCollider(collider);

	stockEffect->Draw();
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
	if (flgInvincible)
		return;

	Sound::GetInstance()->SetPlaySE(PLAYERDAMAGE, true, (Sound::GetInstance()->changevol / 10.0f));
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
		5.0f,
		1.5f
	};

	animation->ChangeAnim(next, shitTime[next], true);
}

/*****************************************
�A�j���[�V�����؂�ւ�����
******************************************/
void Player::ChargeBomber()
{
	D3DXVECTOR3 setPos = transform.pos + D3DXVECTOR3(0.0f, 0.0f, 60.0f);
	GameParticleManager::Instance()->SetPlayerCharge(&setPos);
}

/*****************************************
�{���o�[�X�g�b�N����
******************************************/
void Player::StockBomber()
{
	stockEffect->Init();
}

/*****************************************
�Փ˒ʒm����
******************************************/
void Player::OnNotified(BoxCollider3DTag other)
{
	if (flgInvincible)
		return;

	Sound::GetInstance()->SetPlaySE(PLAYERDAMAGE, true, (Sound::GetInstance()->changevol / 10.0f));
	SpikeNoiseController::Instance()->SetNoise(0.5f, 20);
	hp -= PLAYER_DAMAGE;

	//���G���ԊJ�n
	cntInvincible = PLAYER_INVINCIBLE_DURATION;
	collider->active = false;
	flgInvincible = true;
}

/*****************************************
�����蔻��؂�ւ�
******************************************/
void Player::EnableCollider(bool state)
{
	collider->active = state;
}

