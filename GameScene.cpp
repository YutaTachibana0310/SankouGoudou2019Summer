//=====================================
//
//�Q�[���V�[������[GameScene.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "GameScene.h"
#include "debugWindow.h"
#include "Game.h"
#include "UIManager.h"
#include "player.h"
#include "player_controller.h"
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
void GameScene::Init()
{
	InitUIManager();
	InitPlayer();
	InitPlayerController();
}

/**************************************
�I������
***************************************/
void GameScene::Uninit()
{
	UninitUIManager();
	UninitPlayer();
}

/**************************************
�X�V����
***************************************/
void GameScene::Update(HWND hWnd)
{
	UpdateUIManager(hWnd);
	UpdatePlayer();
	UpdatePlayerController(hWnd);

}

/**************************************
�`�揈��
***************************************/
void GameScene::Draw()
{
	DrawUIManager();
	DrawPlayer();
}