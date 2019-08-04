//=====================================
//
//�v���C���[�w�b�_[player.h]
//Author:GP12B332 12 ����
//
//=====================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "Framework/MeshContainer.h"
#include "PlayerTrail.h"
#include "IStateMachine.h"
#include "TrailCollider.h"
#include "Framework\BaseObserver.h"
#include "Framework\AnimContainer.h"

/**************************************
�}�N����`
***************************************/
enum PlayerAnimID
{
	Flying,
	Attack,
	PlayerAnimMax
};

/**************************************
�v���C���[�N���X��`
***************************************/
class Player : public BaseObserver
{
public:
	Player();
	~Player();

	AnimContainer* animation;
	Transform transform;
	TrailCollider *collider;
	float hp;

	bool active;
	int	cntFrame;
	int inputInterval;				//���͊Ԋu

	bool flgInvincible;				//���G���
	int cntInvincible;				//���G�t���[��

	D3DXVECTOR3	initpos;			// �ړ��O�ʒu
	D3DXVECTOR3	goalpos;			// �ړ���ʒu

	IStateMachine<Player> *state;

	//�֐�
	void ChangeState(IStateMachine<Player> *next);
	void Init();
	void Uninit();
	int Update();
	void Draw();

	void OnNotified(ObserveSubject* notifier);

};

#endif
