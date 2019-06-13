//=====================================
//
//�v���C���[�o���b�g�w�b�_[PlayerBullet.h]
//Author:GP12B332 21 ����
//
//=====================================
#ifndef _PLAYERBULLET_H_
#define _PLAYERBULLET_H_

#include "main.h"
#include "TrailCollider.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/

/**************************************
�v���g�^�C�v�錾
***************************************/
class PlayerBullet
{
public:
	PlayerBullet();
	~PlayerBullet();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void Set(TrailIndex start, TrailIndex end);
	TrailCollider GetCollider();
	bool IsActive();

	//�e�X�g�p
	void Set(D3DXVECTOR3 start, D3DXVECTOR3 end);
	D3DXVECTOR3 pos;

private:
	bool active;
	TrailCollider collider;
	LPDIRECT3DVERTEXBUFFER9 vtxBuff;
	LPDIRECT3DTEXTURE9 texture;
};

#endif