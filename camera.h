//=====================================
//
//�J�����w�b�_[Camera.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"
#include "Framework/BaseSingleton.h"
#include "Framework/Transform.h"

#include <vector>

class BaseCameraPlugin;
/**************************************
Camera�N���X
***************************************/
class Camera : public BaseSingleton<Camera>
{
	friend class BaseSingleton<Camera>;
public:
	void Init();		//������
	void Update();		//�X�V
	void Set();			//�J������񔽉f����

	//�^�������[���h���W���X�N���[�����W�ɕϊ�����֐�
	void Projection(D3DXVECTOR3& out, const D3DXVECTOR3& pos);

	//�^�����X�N���[�����W�����[���h���W�ɕϊ�����֐�
	void UnProjection(D3DXVECTOR3& out, const D3DXVECTOR3& pos, float z);

protected:
	//SRT���
	Transform transform;

	//�����_
	D3DXVECTOR3 target;

	//���_�A�����_�A������i��Ɨp�̈�j
	D3DXVECTOR3 eyeWork;
	D3DXVECTOR3 targetWork;
	D3DXVECTOR3 upWork;

	//����p�A�A�X�y�N�g��A�j�A�l�A�t�@�[�l
	float viewAngle;
	float viewAspect;
	float viewNear;
	float viewFar;

	//�r���[�A�v���W�F�N�V�����s��A�r���[�|�[�g�s��
	D3DXMATRIX view, projection, viewport;
	D3DXMATRIX VPV;

	//�r���[�A�v���W�F�N�V�����A�r���[�|�[�g�t�s��
	D3DXMATRIX invView, invProjection, intViewport;
	D3DXMATRIX invVPV;

	//�v���O�C�����X�g
	std::vector<BaseCameraPlugin*> pluginList;

private:
	Camera();
	Camera(const Camera&) {}
	~Camera() {}

public:
	//�J������h�炷�v���O�C��
	class ShakePlugin;

};

/**************************************
�J�����v���O�C�����N���X
***************************************/
class BaseCameraPlugin
{
public:
	virtual void Update() = 0;
	virtual void Apply(Camera& camera) = 0;
};

#endif