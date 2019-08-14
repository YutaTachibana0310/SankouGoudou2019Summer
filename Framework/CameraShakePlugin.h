//=====================================
//
//�J�����V�F�C�N�v���O�C���w�b�_[ShakePlugin.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _CAMERASHAKEPLUGIN_H_
#define _CAMERASHAKEPLUGIN_H_

#include "../Camera.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class Camera::ShakePlugin : public BaseCameraPlugin, public BaseSingleton<ShakePlugin>
{
	friend class BaseSingleton<ShakePlugin>;
public:
	void Update();
	void Apply(Camera& camera);
	void Set(const D3DXVECTOR3& amplitude, int duration = 30);

private:
	int cntFrame;
	D3DXVECTOR3 amplitude;
	int duration;
	bool active;

	ShakePlugin();
	ShakePlugin(const ShakePlugin&) {}
	~ShakePlugin() {}
};

#endif