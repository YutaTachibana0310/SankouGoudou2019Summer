//=====================================
//
//�v���C���[�o���b�g�w�b�_[PlayerBullet.h]
//Author:GP12B332 21 ����
//
//=====================================
#ifndef _PLAYERBULLET_H_
#define _PLAYERBULLET_H_

#include "main.h"
#include "Framework\BaseObserver.h"
#include "TrailCollider.h"
#include "LineTrailModel.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/

/**************************************
�v���g�^�C�v�錾
***************************************/
class PlayerBullet : public BaseObserver
{
public:
	PlayerBullet();							//�R���X�g���N�^
	~PlayerBullet();						//�f�X�g���N�^

	void Init(LineTrailModel model);		//����������
	void Uninit();							//�I������
	void Update();							//�X�V����
	void Draw();							//�`�揈��

	void OnNotified();
	bool active;

private:
	D3DXVECTOR3 pos;
	TrailCollider *collider;
	LPDIRECT3DVERTEXBUFFER9 vtxBuff;
	int cntFrame;
	D3DXVECTOR3 vtxUp;

	void SetEdgePos(LineTrailModel model);

	static int instanceCount;
	static LPDIRECT3DTEXTURE9 texture;
};

#endif