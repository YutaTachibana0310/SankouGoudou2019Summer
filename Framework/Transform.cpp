//=====================================
//
//�g�����X�t�H�[������[Transform.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "Transform.h"

/**************************************
�R���X�g���N�^
***************************************/
Transform::Transform()
{
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

/**************************************
�R���X�g���N�^
***************************************/
Transform::Transform(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale)
{
	this->pos = pos;
	this->rot = rot;
	this->scale = scale;
}

/**************************************
��]����
***************************************/
void Transform::Rotate(float degX, float degY, float degZ)
{
	rot.x += D3DXToRadian(degX);
	rot.y += D3DXToRadian(degY);
	rot.z += D3DXToRadian(degZ);
}

/**************************************
���[���h�ϊ��s��v�Z
***************************************/
void Transform::CalcWorldMtx(D3DXMATRIX* out)
{
	D3DXMATRIX rotation, scaling, translation;

	//������
	D3DXMatrixIdentity(out);

	//�X�P�[�����O
	D3DXMatrixScaling(&scaling, scale.x, scale.y, scale.z);
	D3DXMatrixMultiply(out, out, &scaling);

	//��]
	D3DXMatrixRotationYawPitchRoll(&rotation, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(out, out, &rotation);

	//�ړ�
	D3DXMatrixTranslation(&translation, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(out, out, &translation);
}

/**************************************
�r���{�[�h�p���[���h�ϊ��s��v�Z����
***************************************/
void Transform::CalcWorldMtx(D3DXMATRIX *out, D3DXMATRIX* invView)
{
	D3DXMATRIX rotation, scaling, translation;

	//������
	D3DXMatrixIdentity(out);

	//�X�P�[�����O
	D3DXMatrixScaling(&scaling, scale.x, scale.y, scale.z);
	D3DXMatrixMultiply(out, out, &scaling);

	//��]
	D3DXMatrixRotationYawPitchRoll(&rotation, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(out, out, &rotation);

	//�r���[�t�ϊ�
	D3DXMatrixMultiply(out, out, invView);

	//�ړ�
	D3DXMatrixTranslation(&translation, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(out, out, &translation);
}