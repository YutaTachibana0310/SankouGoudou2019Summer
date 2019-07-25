//=====================================
//
//�g�����X�t�H�[���w�b�_[Transform.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "../main.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class Transform
{
public:
	D3DXVECTOR3 pos;	//���W
	D3DXVECTOR3 rot;	//��]
	D3DXVECTOR3 scale;	//�X�P�[��

	//�R���X�g���N�^
	Transform();
	Transform(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale);

	//��]����
	void Rotate(float degX, float degY, float degZ);

	//���[���h�ϊ��s��v�Z����
	void CalcWorldMtx(D3DXMATRIX* out);

	//�r���{�[�h�p���[���h�ϊ��s��v�Z����
	void CalcWorldMtx(D3DXMATRIX* out, D3DXMATRIX *invView);
};

#endif