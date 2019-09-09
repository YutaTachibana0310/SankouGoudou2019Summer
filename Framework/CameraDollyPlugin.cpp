//=====================================
//
//CameraDollyPlugin.cpp
//�@�\:�J�����h�[���[�v���O�C��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "CameraDollyPlugin.h"
#include "Easing.h"
#include "Vector3.h"

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
�X�V����
***************************************/
void Camera::DollyPlugin::Update()
{
	if (cntFrame >= duration)
		return;

	cntFrame++;
}

/**************************************
�v���O�C���K�p����
***************************************/
void Camera::DollyPlugin::Apply(Camera & camera)
{
	//�����̕ω��ʂ��C�[�W���O�ŋ��߂�
	if (cntFrame < duration)
	{
		float t = 1.0f * cntFrame / duration;
		currentLength = Easing::EaseValue(t, startLength, deltaLength, EaseType::OutCubic);
	}

	//�J�������_�ɋ����̕ω��ʂ�������
	camera.eyeWork += currentLength;
}

/**************************************
�Z�b�g����
***************************************/
void Camera::DollyPlugin::Set(const D3DXVECTOR3 & deltaLegnth, int duration)
{
	this->cntFrame = 0;
	this->deltaLength = deltaLegnth;
	this->startLength = this->currentLength;
	this->duration = duration;
}

/**************************************
�R���X�g���N�^
***************************************/
Camera::DollyPlugin::DollyPlugin() :
	cntFrame(0),
	deltaLength(Vector3::Zero),
	startLength(Vector3::Zero),
	currentLength(Vector3::Zero),
	duration(0)
{

}