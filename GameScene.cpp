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

#include "EnemyController.h"
/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static Enemy* enemy[ENMEY_MAX];
/**************************************
����������
***************************************/
void GameScene::Init()
{
	InitSkyBox(0);
	InitBackGroundCity(0);
	InitUIManager();

	//�G�l�~�[�̏�����
	for (int i = 0; i <= ENMEY_MAX; i++)
	{
		enemy[i] = new EnemyStraight;
		enemy[i]->Init();
	}
}

/**************************************
�I������
***************************************/
void GameScene::Uninit()
{
	UninitSkyBox(0);
	UninitBackGroundCity(0);

	UninitUIManager();

	//�G�l�~�[�̏I������
	for (int i = 0; i <= ENMEY_MAX; i++)
	{
		enemy[i]->Uninit(enemy[i]);
	}

}

/**************************************
�X�V����
***************************************/
void GameScene::Update(HWND hWnd)
{
	UpdateSkyBox();
	UpdateBackGroundCity();
	UpdateUIManager(hWnd);

	//�G�l�~�[�̍X�V����
	for (int i = 0; i <= ENMEY_MAX; i++)
	{
		enemy[i]->Update(hWnd);
	}

}

/**************************************
�`�揈��
***************************************/
void GameScene::Draw()
{
	DrawSkyBox();

	DrawBackGroundCity();

	DrawUIManager();

	//�G�l�~�[�̕`�揈��
	for (int i = 0; i <= ENMEY_MAX; i++)
	{
		enemy[i]->Draw();
	}
	BeginDebugWindow("count");
	DebugText("objNum:%d", Enemy::objNum);
	EndDebugWindow("count");
}