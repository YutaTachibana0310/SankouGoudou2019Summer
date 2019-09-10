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
#include "ResultPlayer.h"

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
	player = new ResultPlayer(false);

	InitResultSceneUI();

}

/**************************************
�I������
***************************************/
void ResultScene::Uninit()
{
	UninitResultSceneUI();

	SAFE_DELETE(player);
}

/**************************************
�X�V����
***************************************/
void ResultScene::Update(HWND hWnd)
{
	player->Update();
	UpdateResultSceneUI(hWnd);
}

/**************************************
�`�揈��
***************************************/
void ResultScene::Draw()
{
	player->Draw();
	DrawResultSceneUI();
}