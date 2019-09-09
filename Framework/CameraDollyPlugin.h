//=====================================
//
//CameraDollyPlugin.h
//�@�\:�J�����h�[���[�v���O�C��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _CAMERADOLLYPLUGIN_H_
#define _CAMERADOLLYPLUGIN_H_

#include "../Camera.h"
#include "BaseSingleton.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class Camera::DollyPlugin : public BaseCameraPlugin, public BaseSingleton<DollyPlugin>
{
	friend class BaseSingleton<DollyPlugin>;
public:
	void Update();
	void Apply(Camera& camera);
	void Set(const D3DXVECTOR3& deltaLegnth, int duration);

private:
	int cntFrame;
	D3DXVECTOR3 deltaLength;
	int duration;

	DollyPlugin();
};

#endif