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
}

/**************************************
�`�揈��
***************************************/
void TitleScene::Draw()
{
	titleSceneUIManager->Draw();
}