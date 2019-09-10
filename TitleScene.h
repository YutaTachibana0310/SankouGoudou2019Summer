//=====================================
//
//�^�C�g���V�[���w�b�_[TitleScene.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _TITLESCENE_H_
#define _TITLESCENE_H_

#include "main.h"
#include "IStateScene.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�O���錾
***************************************/
class TitleSceneUIManager;
class BackGroundController;

/**************************************
�N���X��`
***************************************/
class TitleScene : public IStateScene
{
public:
	void Init();
	void Uninit();
	void Update(HWND hWnd);
	void Draw();

	TitleScene() {};
	~TitleScene() {};

private:
	TitleSceneUIManager *titleSceneUIManager;
	BackGroundController *bgController;
};

#endif