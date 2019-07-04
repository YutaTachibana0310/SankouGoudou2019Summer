//=====================================
//
//�Q�[���V�[������[GameScene.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "GameScene.h"
#include "debugWindow.h"
#include "Game.h"
#include "LineTrailModel.h"
#include "PostEffectManager.h"
#include "debugWindow.h"
#include "debugTimer.h"

#include "GameSceneUIManager.h"
#include "player.h"
#include "PlayerController.h"
#include "InputController.h"

#include "BackGroundCity.h"
#include "BackGroundRoad.h"
#include "BackGroundField.h"
#include "SkyBox.h"
#include "GameParticleManager.h"

#include "sound.h"
#include "TrailCollider.h"

#include "EnemyController.h"


#include "Enemy.h"

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

Enemy *enemy[100];	//test�p

/**************************************
����������
***************************************/
void GameScene::Init()
{
	//�C���X�^���X����
	enemyController = new EnemyController();

	//UI������
	InitGameSceneUI();

	//���{�^���̈ʒu���烏�[���h���W���v�Z
	LineTrailModel::CalcEdgePosition();

	//�w�i������
	InitSkyBox(0);
	InitBackGroundCity(0);
	InitBackGroundRoad();
	InitBackGroundField();

	//�p�[�e�B�N��������
	InitGameParticleManager(0);

	//�v���C���[������
	InitPlayerController();

	//�T�E���h������
	Sound::GetInstance()->Create();
#if 0
	//�G�l�~�[test
	for (int i = 0; i < 50; i++)
	{
		enemy[i] = new EnemyStraight;
		enemy[i]->Init();
	}

	for (int i = 50; i < 100; i++)
	{
		enemy[i] = new EnemyChange;
		enemy[i]->Init();
	}

	for (int nCntEnemy = 0, i = 0; nCntEnemy < 50, i < 4; nCntEnemy++, i++)
	{
		if (!enemy[nCntEnemy]->active)
		{		
			enemy[nCntEnemy]->Set(D3DXVECTOR3(0.0f + 20.f*i, 50.0f, 15.0f), D3DXVECTOR3(0.0f + 20.f*i, 0.0f, 0.0f),200);
			
		}
	}

	for (int nCntEnemy = 50, i = 0; nCntEnemy < 100, i < 4; nCntEnemy++, i++)
	{
		if (!enemy[nCntEnemy]->active)
		{
			
			enemy[nCntEnemy]->SetVec(D3DXVECTOR3(0.0f + 20.f*i, 50.0f, 15.0f), D3DXVECTOR3(0.0f + 20.f*i, 20.0f, 0.0f), 200,50, D3DXVECTOR3 (3.0f,0.0f,-5.0f));
			
		}
	}
#endif

	//�G�l�~�[������
	enemyController->Init();

	//�v���t�@�C����GameScene��o�^
	RegisterDebugTimer(GAMESCENE_LABEL);

}

/**************************************
�I������
***************************************/
void GameScene::Uninit()
{
	//�w�i�I��
	UninitSkyBox(0);
	UninitBackGroundCity(0);
	UninitBackGroundRoad();
	UninitBackGroundField();

	//�p�[�e�B�N���I��
	UninitGameParticleManager(0);

	//�v���C���[�I��
	UninitPlayerController();

#if 0
	//�G�l�~�[test
	for (int i = 0; i < 100; i++)
	{
		enemy[i]->Uninit();
	}
#endif

	//�G�l�~�[�I��
	enemyController->Uninit();

	//UI�I��
	UninitGameSceneUI();

	//�C���X�^���X�폜
	SAFE_DELETE(enemyController);
}

/**************************************
�X�V����
***************************************/
void GameScene::Update(HWND hWnd)
{
	//�T�E���h�Đ�(�e�X�g�j
	InputSound();

	//�w�i�I�u�W�F�N�g�̍X�V
	CountDebugTimer(GAMESCENE_LABEL, "UpdateBG");
	UpdateSkyBox();
	UpdateBackGroundCity();
	UpdateBackGroundRoad();
	UpdateBackGroundField();
	CountDebugTimer(GAMESCENE_LABEL, "UpdateBG");

	//�v���C���[�̍X�V
	CountDebugTimer(GAMESCENE_LABEL, "UpdatePlayer");
	UpdatePlayerController(hWnd);
	CountDebugTimer(GAMESCENE_LABEL, "UpdatePlayer");

	//�G�l�~�[�̍X�V
#if 0
	for (int i = 0; i < 100; i++)
	{
		enemy[i]->Update();
	}
#endif
	enemyController->Update();


	//�p�[�e�B�N���̍X�V
	CountDebugTimer(GAMESCENE_LABEL, "UpdateParticle");
	UpdateGameParticleManager();
	CountDebugTimer(GAMESCENE_LABEL, "UpdateParticle");

	//UI�̍X�V
	CountDebugTimer(GAMESCENE_LABEL, "UpdateUI");
	UpdateGameSceneUI(hWnd);
	CountDebugTimer(GAMESCENE_LABEL, "UpdateUI");

	//�|�X�g�G�t�F�N�g�̍X�V
	PostEffectManager::Instance()->Update();

	//�Փ˔���
	TrailCollider::UpdateCollision();
}

/**************************************
�`�揈��
***************************************/
void GameScene::Draw()
{

	//�w�i�̕`��
	CountDebugTimer(GAMESCENE_LABEL, "DrawBG");
	DrawSkyBox();
	DrawBackGroundCity();
	DrawBackGroundRoad();
	DrawBackGroundField();
	CountDebugTimer(GAMESCENE_LABEL, "DrawBG");

	//�v���C���[�̕`��
	CountDebugTimer(GAMESCENE_LABEL, "DrawPlayer");
	DrawPlayerController();
#if 0
	//�G�l�~�[test
	for (int i = 0; i < 100; i++)
	{
		enemy[i]->Draw();
	}

#endif

	CountDebugTimer(GAMESCENE_LABEL, "DrawPlayer");

	//�G�l�~�[�̕`��
	enemyController->Draw();

	//�|�X�g�G�t�F�N�g�`��
	CountDebugTimer(GAMESCENE_LABEL, "DrawpostEffect");
	PostEffectManager::Instance()->Draw();
	CountDebugTimer(GAMESCENE_LABEL, "DrawpostEffect");

	//�p�[�e�B�N���`��
	CountDebugTimer(GAMESCENE_LABEL, "DrawParticle");
	DrawGameParticleManager();
	CountDebugTimer(GAMESCENE_LABEL, "DrawParticle");


	//UI�`��
	DrawGameSceneUI();

	DrawDebugTimer(GAMESCENE_LABEL);
}