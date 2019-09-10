//=====================================
//
//�^�C�g���V�[������[TitleScene.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "TitleScene.h"
#include "debugWindow.h"
#include "Game.h"
#include "InputController.h"
#include "TitleSceneUIManager.h"
#include "sound.h"
#include "InputController.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
����������
***************************************/
void TitleScene::Init()
{

	titleSceneUIManager = new TitleSceneUIManager();

	titleSceneUIManager->Init();

}

/**************************************
�I������
***************************************/
void TitleScene::Uninit()
{
	SAFE_DELETE(titleSceneUIManager);
	titleSceneUIManager->Uninit();
}

/**************************************
�X�V����
***************************************/
void TitleScene::Update(HWND hWnd)
{
	titleSceneUIManager->Update(hWnd);

	if (IsAnyKeyTriggered() || IsAnyButtonTriggerd())
	{
		//SE
		Sound::GetInstance()->SetPlaySE(ENTERSE, Sound::GetInstance()->enterSE, (Sound::GetInstance()->changevol / 5.0f));
		SceneChangeFlag(true, Scene::SceneGame);
	}
}

/**************************************
�`�揈��
***************************************/
void TitleScene::Draw()
{
	titleSceneUIManager->Draw();
}