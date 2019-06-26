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
	PlayerBullet();		//�R���X�g���N�^
	~PlayerBullet();	//�f�X�g���N�^

	void Init();		//����������
	void Uninit();		//�I������
	void Update();		//�X�V����
	void Draw();		//�`�揈��

	void SetTrailIndex(TrailIndex start, TrailIndex end);		//�g���C���C���f�b�N�X�Z�b�g����
	void SetEdgePos(D3DXVECTOR3 *left, D3DXVECTOR3 *right);	//�[�_�ݒ菈��
	TrailCollider GetCollider();	//�����蔻��擾����
	bool IsActive();				//�A�N�e�B�u����
	bool active;

private:
	D3DXVECTOR3 pos;
	TrailCollider collider;
	LPDIRECT3DVERTEXBUFFER9 vtxBuff;
	int cntFrame;
	D3DXVECTOR3 vtxUp;

	static int instanceCount;
	static LPDIRECT3DTEXTURE9 texture;
};

#endif