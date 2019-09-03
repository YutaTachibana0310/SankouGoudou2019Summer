//=====================================
//
//�e���v���[�g����[Vector3.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "Vector3.h"
#include "TMath.h"
#include "Easing.h"

/**************************************
�}�N����`
***************************************/

/**************************************
static�����o
***************************************/
const D3DXVECTOR3 Vector3::Right = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
const D3DXVECTOR3 Vector3::Left = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
const D3DXVECTOR3 Vector3::Forward = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
const D3DXVECTOR3 Vector3::Back = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
const D3DXVECTOR3 Vector3::Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
const D3DXVECTOR3 Vector3::Down = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
const D3DXVECTOR3 Vector3::One = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
const D3DXVECTOR3 Vector3::Zero = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

/**************************************
Max�֐�
***************************************/
D3DXVECTOR3 Vector3::Max(const D3DXVECTOR3& arg1, const D3DXVECTOR3& arg2)
{
	float length1 = D3DXVec3LengthSq(&arg1);
	float length2 = D3DXVec3LengthSq(&arg2);

	return length1 >= length2 ? arg1 : arg2;
}

/**************************************
Min�֐�
***************************************/
D3DXVECTOR3 Vector3::Min(const D3DXVECTOR3& arg1, const D3DXVECTOR3& arg2)
{
	float length1 = D3DXVec3LengthSq(&arg1);
	float length2 = D3DXVec3LengthSq(&arg2);

	return length1 <= length2 ? arg1 : arg2;
}

/**************************************
Clampn�֐�
***************************************/
D3DXVECTOR3 Vector3::Clamp(const D3DXVECTOR3& min, const D3DXVECTOR3& max, const D3DXVECTOR3& arg)
{
	D3DXVECTOR3 wk;
	wk.x = Math::Clamp(min.x, max.x, arg.x);
	wk.y = Math::Clamp(min.y, max.y, arg.y);
	wk.z = Math::Clamp(min.z, max.z, arg.z);

	return wk;
}

/**************************************
Lerp�֐�
***************************************/
D3DXVECTOR3 Vector3::Lerp(float t, D3DXVECTOR3& min, const D3DXVECTOR3& max)
{
	return Easing::EaseValue(t, min, max, EaseType::Linear);
}

/**************************************
Slerp�֐�
***************************************/
D3DXVECTOR3 Vector3::Slerp(float t, const D3DXVECTOR3& from, const D3DXVECTOR3& to)
{
	D3DXVECTOR3 nFrom, nTo;
	D3DXVec3Normalize(&nFrom, &from);
	D3DXVec3Normalize(&nTo, &to);

	float angle = acosf(D3DXVec3Dot(&nFrom, &nTo));

	float sin = sinf(angle);

	float Ps = sinf(angle * (1 - t));
	float Pe = sinf(angle * t);

	D3DXVECTOR3 out = (Ps * nFrom + Pe * nTo) / sin;
	D3DXVec3Normalize(&out, &out);

	return out;
}

/**************************************
Angle�֐�
***************************************/
float Vector3::Angle(const D3DXVECTOR3& from, const D3DXVECTOR3& to)
{
	D3DXVECTOR3 normalize1, normalize2;
	D3DXVec3Normalize(&normalize1, &from);
	D3DXVec3Normalize(&normalize2, &to);

	return D3DXToDegree(acosf(D3DXVec3Dot(&normalize1, &normalize2)));
}

/**************************************
JudgeDirection�֐�
***************************************/
D3DXVECTOR3 Vector3::Axis(const D3DXVECTOR3& from, const D3DXVECTOR3& to)
{
	D3DXVECTOR3 cross;

	D3DXVec3Cross(&cross, &from, &to);

	D3DXVec3Normalize(&cross, &cross);

	return cross;
}

/**************************************
Distance�֐�
***************************************/
float Vector3::Distance(const D3DXVECTOR3& from, const D3DXVECTOR3& to)
{
	D3DXVECTOR3 diff = to - from;

	return D3DXVec3Length(&diff);
}