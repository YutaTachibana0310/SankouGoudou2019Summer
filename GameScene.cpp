//=====================================
//
//�Q�[���V�[������[GameScene.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "GameScene.h"
#include "debugWindow.h"
#include "Game.h"
#include "PostEffectManager.h"
#include "debugWindow.h"
#include "debugTimer.h"

#include "UIManager.h"
#include "cursor.h"
#include "player.h"
#include "PlayerController.h"
#include "InputController.h"

#include "BackGroundCity.h"
#include "BackGroundRoad.h"
#include "BackGroundField.h"
#include "SkyBox.h"
#include "GameParticleManager.h"

#include "player.h"
#include "PlayerBullet.h"

#include "CollisionManager.h"

/**************************************
�}�N����`
***************************************/
#define GAMESCENE_LABEL ("GameScene")

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
	InitSkyBox(0);
	InitBackGroundCity(0);

	InitBackGroundRoad();
	InitBackGroundField();

	InitGameParticleManager(0);

	InitUI();

	InitPlayerController();
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

	UninitGameParticleManager(0);

	UninitPlayerController();

	UninitUI();
	UninitCursor();

}

/**************************************
�X�V����
***************************************/
void GameScene::Update(HWND hWnd)
{
	//�w�i�I�u�W�F�N�g�̍X�V
	UpdateSkyBox();
	UpdateBackGroundCity();
	UpdateBackGroundRoad();
	UpdateBackGroundField();

	//�v���C���[�̍X�V
	UpdatePlayerController(hWnd);

	//�p�[�e�B�N���̍X�V
	UpdateGameParticleManager();

	//UI�̍X�V
	UpdateUI(hWnd);
	UpdateCursor(hWnd);

	//�|�X�g�G�t�F�N�g�̍X�V
	PostEffectManager::Instance()->Update();

	//�Փ˔���
	UpdateCollisionManager();
}

/**************************************
�`�揈��
***************************************/
void GameScene::Draw()
{
	//�w�i�̕`��
	DrawSkyBox();
	DrawBackGroundCity();
	DrawBackGroundRoad();
	DrawBackGroundField();

	//�v���C���[�̕`��
	DrawPlayerController();

	//�v���C���[�o���b�g�`��
	DrawPlayerBullet();

	//�|�X�g�G�t�F�N�g�`��
	PostEffectManager::Instance()->Draw();

	//�p�[�e�B�N���`��
	DrawGameParticleManager();

	
	//UI�`��
	DrawUI();
	DrawCursor();
}