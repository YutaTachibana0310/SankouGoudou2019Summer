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

PlayerBullet *tmp;
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

	InitGameParticleManager(0);

	InitUI();

	InitPlayerController();
	player.Init();
	InitCursor();

	tmp = new PlayerBullet();
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

	UninitUI();

	player.Uninit();
	UninitCursor();
}

/**************************************
�X�V����
***************************************/
void GameScene::Update(HWND hWnd)
{
	BeginDebugWindow("Bullet");
	if (DebugButton("Fire"))
	{
		tmp->Set(D3DXVECTOR3(-100.0f, RandomRangef(-100.0f, 100.0f), 0.0f), D3DXVECTOR3(100.0f, RandomRangef(-100.0f, 100.0f), 0.0f));
	}
	EndDebugWindow("Bullet");

	//�w�i�I�u�W�F�N�g�̍X�V
	UpdateSkyBox();
	UpdateBackGroundCity();
	UpdateBackGroundRoad();
	UpdateBackGroundField();

	//�v���C���[�̍X�V
	UpdatePlayerController(hWnd);
	player.Update();
	tmp->Update();

	//�p�[�e�B�N���̍X�V
	UpdateGameParticleManager();

	//UI�̍X�V
	UpdateUI(hWnd);
	UpdateCursor(hWnd);

	//�|�X�g�G�t�F�N�g�̍X�V
	PostEffectManager::Instance()->Update();
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
	player.Draw();
	tmp->Draw();

	//�p�[�e�B�N���`��
	DrawGameParticleManager();

	//�|�X�g�G�t�F�N�g�`��
	//PostEffectManager::Instance()->Draw();
	
	//UI�`��
	DrawUI();
	DrawCursor();
}