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
#include <functional>

/**************************************
�}�N����`
***************************************/


/**************************************
�v���C���[�N���X��`
***************************************/
class Player
{
public:
	Player();
	~Player();

	MeshContainer* mesh;
	Transform transform;

	bool active;
	int	cntFrame;

	D3DXVECTOR3	initpos;			// �ړ��O�ʒu
	D3DXVECTOR3	goalpos;			// �ړ���ʒu

	IStateMachine<Player> *state;
	PlayerTrail *trail;

	//�֐�
	void ChangeState(IStateMachine<Player> *next);
	void Init();
	void Uninit();
	int Update();
	void Draw();
};

#endif
