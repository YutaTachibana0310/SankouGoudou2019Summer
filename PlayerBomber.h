//=====================================
//
//�v���C���[�w�b�_[player.h]
//Author:GP12B332 12 ����
//
//=====================================
#ifndef _PLAYERBOMBER_H_
#define _PLAYERBOMBER_H_

#include "main.h"
#include "Framework/MeshContainer.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/


/**************************************
�v���g�^�C�v�錾
***************************************/
class PlayerBomber
{
public:
	PlayerBomber();				//�R���X�g���N�^
	~PlayerBomber();				//�f�X�g���N�^

	void Init();				//����������
	void Uninit();				//�I������
	void Update();				//�X�V����
	void Draw();				//�`�揈��

	void Set(D3DXVECTOR3 *pos,D3DXVECTOR3 initpos);
	void CalcBomber(void);

	MeshContainer* mesh;

	Transform transform;
	D3DXVECTOR3 *targetPos;
	D3DXVECTOR3 velocity;
	bool active;
	int cntFrame;
	int reachFrame;
	LPDIRECT3DVERTEXBUFFER9 vtxBuff;
	D3DXVECTOR3 vtxUp;

	static int instanceCount;
	static LPDIRECT3DTEXTURE9 texture;

};





#endif