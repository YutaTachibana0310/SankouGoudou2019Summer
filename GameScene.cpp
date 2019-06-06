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

#include "BackGroundCity.h"
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
	InitUIManager();

	player.Init();
}

/**************************************
�I������
***************************************/
void GameScene::Uninit()
{
	UninitSkyBox(0);
	UninitBackGroundCity(0);

	UninitUIManager();

	player.Uninit();
}

/**************************************
�X�V����
***************************************/
void GameScene::Update(HWND hWnd)
{
	UpdateSkyBox();
	UpdateBackGroundCity();
	UpdateUIManager(hWnd);
	player.Update();
}

/**************************************
�`�揈��
***************************************/
void GameScene::Draw()
{
	DrawSkyBox();

	DrawBackGroundCity();

	DrawUIManager();

	player.Draw();
}