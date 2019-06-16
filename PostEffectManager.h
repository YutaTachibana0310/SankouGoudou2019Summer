//=====================================
//
//�|�X�g�G�t�F�N�g�}�l�[�W���w�b�_[PostEffectManager.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _POSTEFFECTMANAGER_H_
#define _POSTEFFECTMANAGER_H_

#include "main.h"
#include "PostEffect\ScreenObject.h"
#include "Framework\BaseSingleton.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class PostEffectManager : public BaseSingleton<PostEffectManager>
{
public:
	friend class BaseSingleton<PostEffectManager>;

	static void Destroy();
	void Update();
	void Draw();

private:
	PostEffectManager();
	~PostEffectManager();

	bool useSceneBloom;
	bool useCrossFilter;
	bool useSpeedBlur;
};


#endif