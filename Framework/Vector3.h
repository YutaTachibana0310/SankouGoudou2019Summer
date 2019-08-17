//=====================================
//
//3�����x�N�g���w�b�_[Vector3.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _VECTOR3_H_
#define _VECTOR3_H_

#include "../../main.h"

/**************************************
�}�N����`
***************************************/

/**************************************
D3DXVECTOR3���[�e�B���e�B�N���X
***************************************/
class Vector3
{
public:
	//�O�㍶�E�㉺
	static const D3DXVECTOR3 Up, Down;
	static const D3DXVECTOR3 Right, Left;
	static const D3DXVECTOR3 Forward, Back;
	static const D3DXVECTOR3 One, Zero;

	//2�̂����傫���x�N�g����Ԃ�
	static D3DXVECTOR3 Max(const D3DXVECTOR3& arg1, const D3DXVECTOR3& arg2);

	//2�̂����������x�N�g����Ԃ�
	static D3DXVECTOR3 Min(const D3DXVECTOR3& arg1, const D3DXVECTOR3& arg2);

	//arg��min�`max�͈̔͂ɐ������ĕԂ�
	static D3DXVECTOR3 Clamp(const D3DXVECTOR3& min, const D3DXVECTOR3& max, const D3DXVECTOR3& arg);

	//min�`max�͈̔͂�t�Ő��`��Ԃ��ĕԂ�
	static D3DXVECTOR3 Lerp(float t, D3DXVECTOR3& min, const D3DXVECTOR3& max);

	//min�`max�͈̔͂�t�ŋ��ʐ��`��Ԃ��ĕԂ�
	static D3DXVECTOR3 Slerp(float t, const D3DXVECTOR3& from, const D3DXVECTOR3& to);

	//2�̃x�N�g�����Ȃ��p�x���I�C���[�p�ŕԂ�
	static float Angle(const D3DXVECTOR3& from, const D3DXVECTOR3& to);

	//2�̃x�N�g���ƒ��s���鎲��Ԃ�
	static D3DXVECTOR3 Axis(const D3DXVECTOR3& from, const D3DXVECTOR3& to);

	//2�̃x�N�g���̋�����Ԃ�
	static float Distance(const D3DXVECTOR3& from, const D3DXVECTOR3& to);
		
private:
	Vector3();
};

#endif