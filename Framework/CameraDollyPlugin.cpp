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
	float t = 1.0f * cntFrame / duration;
	D3DXVECTOR3 length = Easing::EaseValue(t, Vector3::Zero, deltaLength, EaseType::OutCubic);

	//�J�������_�ɋ����̕ω��ʂ�������
	camera.eyeWork += length;
}

/**************************************
�Z�b�g����
***************************************/
void Camera::DollyPlugin::Set(const D3DXVECTOR3 & deltaLegnth, int duration)
{
	this->cntFrame = 0;
	this->deltaLength = deltaLegnth;
	this->duration = duration;
}

/**************************************
�R���X�g���N�^
***************************************/
Camera::DollyPlugin::DollyPlugin() :
	cntFrame(0),
	deltaLength(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	duration(0)
{

}