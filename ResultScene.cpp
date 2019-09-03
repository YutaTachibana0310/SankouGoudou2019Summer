//=====================================
//
//���U���g�V�[������[ResultScene.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "ResultScene.h"
#include "debugWindow.h"
#include "Game.h"
#include "ResultSceneUIManager.h"


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
void ResultScene::Init()
{
	resultSceneUIManager = new ResultSceneUIManager;

	resultSceneUIManager->Init();
}

/**************************************
�I������
***************************************/
void ResultScene::Uninit()
{
	SAFE_DELETE(resultSceneUIManager);
	resultSceneUIManager->Uninit();
}

/**************************************
�X�V����
***************************************/
void ResultScene::Update(HWND hWnd)
{
	resultSceneUIManager->Update(hWnd);
}

/**************************************
�`�揈��
***************************************/
void ResultScene::Draw()
{
	resultSceneUIManager->Draw();
}