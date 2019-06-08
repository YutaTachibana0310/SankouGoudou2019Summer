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
#include "cursor.h"
#include "player.h"
#include "PlayerController.h"
#include "InputController.h"

#include "BackGroundCity.h"
#include "BackGroundRoad.h"
#include "BackGroundField.h"
#include "SkyBox.h"

#include "player.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
class Player player;
/**************************************
����������
***************************************/
void GameScene::Init()
{
	InitSkyBox(0);
	InitBackGroundCity(0);
	InitBackGroundRoad();
	InitBackGroundField();
	InitUI();

	InitPlayerController();
	player.Init();
	InitCursor();
}

/**************************************
�I������
***************************************/
void GameScene::Uninit()
{
	UninitSkyBox(0);
	UninitBackGroundCity(0);
	UninitBackGroundRoad();
	UninitBackGroundField();

	UninitUI();

	player.Uninit();
	UninitCursor();
}

/**************************************
�X�V����
***************************************/
void GameScene::Update(HWND hWnd)
{
	UpdateSkyBox();
	UpdateBackGroundCity();
	UpdateBackGroundRoad();
	UpdateBackGroundField();
	UpdateUI(hWnd);
	UpdatePlayerController(hWnd);
	player.Update();
	UpdateCursor(hWnd);
}

/**************************************
�`�揈��
***************************************/
void GameScene::Draw()
{
	DrawSkyBox();

	DrawBackGroundCity();

	DrawBackGroundRoad();

	DrawBackGroundField();

	DrawUI();

	player.Draw();

	DrawCursor();
}