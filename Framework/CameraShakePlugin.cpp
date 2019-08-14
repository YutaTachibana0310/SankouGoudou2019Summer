//=====================================
//
//�e���v���[�g����[ShakePlugin.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "CameraShakePlugin.h"
#include "Easing.h"

/**************************************
�}�N����`
***************************************/

/**************************************
ShakePlugin�R���X�g���N�^
***************************************/
Camera::ShakePlugin::ShakePlugin()
{
	cntFrame = 0;
	ZeroMemory(&amplitude, sizeof(amplitude));
	duration = 0;
	active = false;
}

/**************************************
ShakePlugin�X�V����
***************************************/
void Camera::ShakePlugin::Update()
{
	if (!active)
		return;

	cntFrame++;

	if (cntFrame == duration)
	{
		active = false;
	}

}

/**************************************
ShakePlugin���f����
***************************************/
void Camera::ShakePlugin::Apply(Camera& camera)
{
	if (!active)
		return;

	float t = (float)cntFrame / duration;
	float range = Easing::EaseValue(t, 1.0f, 0.0f, EaseType::OutCirc);

	D3DXVECTOR3 offset;
	offset.x = Math::RandomRange(-range, range) * amplitude.x;
	offset.y = Math::RandomRange(-range, range) * amplitude.y;
	offset.z = Math::RandomRange(-range, range) * amplitude.z;

	camera.eyeWork += offset;
	camera.targetWork += offset;
}

/**************************************
ShakePlugin�Z�b�g����
***************************************/
void Camera::ShakePlugin::Set(const D3DXVECTOR3& amplitude, int duration)
{
	cntFrame = 0;
	this->amplitude = amplitude;
	this->duration = duration;
	active = true;
}