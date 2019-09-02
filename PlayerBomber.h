//=====================================
//
//�v���C���[�{���o�[�w�b�_[PlayerBomber.h]
//Author:GP12B332 12 ����
//
//=====================================
#ifndef _PLAYERBOMBER_H_
#define _PLAYERBOMBER_H_

#include "main.h"
#include "Framework\BoxCollider3D.h"
#include "enemy.h"
#include "BossEnemyModel.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/

/**************************************
�v���g�^�C�v�錾
***************************************/
class PlayerBomber : public ColliderObserver
{
public:
	PlayerBomber();						//�R���X�g���N�^
	virtual ~PlayerBomber();			//�f�X�g���N�^

	//����������
	void Init(const D3DXVECTOR3& moveDir);
	void Uninit();				//�I������
	virtual void Update() = 0;	//�X�V����
	void Draw();				//�`�揈��

	void Homing(void);
	void OnNotified(BoxCollider3DTag other);

	bool active;

protected:
	Transform transform;
	D3DXVECTOR3 targetPos;
	D3DXVECTOR3 velocity;
	int cntFrame;
	int reachFrame;

	static int instanceCount;

	void Set(D3DXVECTOR3 initPos);

private:
	BoxCollider3D* collider;

};

#endif