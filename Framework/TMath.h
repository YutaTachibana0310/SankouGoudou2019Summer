//=====================================
//
//���w�w�b�_[TMath.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _TMATH_H_
#define _TMATH_H_

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class Math
{
public:
	/**************************************
	�����擾����
	***************************************/
	static int RandomRange(int min, int max)
	{
		return rand() % (max - min) + min;
	}

	static float RandomRange(float min, float max)
	{
		return (float)rand() / RAND_MAX * (max - min) + min;
	}

	/**************************************
	�召����
	***************************************/
	template <typename T>
	static T Max(T v1, T v2)
	{
		return v1 < v2 ? v2 : v1;
	}

	template <typename T>
	static T Min(T v1, T v2)
	{
		return v1 > v2 ? v2 : v1;
	}

	/**************************************
	���b�v����
	***************************************/
	static int WrapAround(int min, int max, int value)
	{
		int mod = (value - min) % (max - min);
		return (mod >= 0) ? mod + min : mod + max;
	}

	static float WrapAround(float min, float max, float value)
	{
		float mod = fmodf(value - min, max - min);
		return (mod >= 0.0f) ? mod + min : mod + max;
	}

	/**************************************
	�N�����v
	***************************************/
	template <typename T>
	static T Clamp(T min, T max, T value)
	{
		return Max(min, Min(max, value));
	}

	/**************************************
	2���x�W�F�Ȑ��֐�
	***************************************/
	template <typename T>
	static T QuadraticBezier(const T& start, const T& end, const T& c, float t)
	{
		return powf(1.0f - t, 2.0f) * start + 2 * t * (1.0f - t) * c + powf(t, 2.0f) * end;
	}

	/**************************************
	3���x�W�F�Ȑ��֐�
	***************************************/
	template<typename T>
	static T CubibBezier(const T&start, const T&end, const T&c1, const T&c2, float t)
	{
		return powf(1.0f - t, 3.0f) * start
			+ 3.0f * powf(1.0f - t, 2.0f) * t * c1
			+ 3.0f * (1.0f - t) * powf(t, 2.0f) * c2
			+ powf(t, 3.0f) * end;
	}
};

#endif