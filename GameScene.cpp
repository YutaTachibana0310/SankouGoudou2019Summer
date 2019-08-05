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
#include "PlayerController.h"
#include "PlayerObserver.h"
#include "InputController.h"
#include "BackGroundController.h"
#include "BackGroundRoad.h"
#include "BackGroundField.h"
#include "GameParticleManager.h"
#include "sound.h"
#include "EnemyController.h"
#include "masktex.h"

#include "GameStart.h"
#include "GameBattle.h"
#include "GameEnd.h"
#include "GameBomberSequence.h"

#include "RebarOb.h"

using namespace std;

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
	//�X�e�[�g�}�V���쐬
	fsm[State::Start] = new GameStart();
	fsm[State::Battle] = new GameBattle();
	fsm[State::End] = new GameEnd();
	fsm[State::BombSequence] = new GameBomberSequence();

	//�Ó]�p�|���S���쐬
	darkMask = new Polygon2D();
	darkMask->SetSize((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	darkMask->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f));
	useDarkMask = false;

	//UI������
	InitGameSceneUI();

	//���{�^���̈ʒu���烏�[���h���W���v�Z
	LineTrailModel::CalcEdgePosition();

	//�C���X�^���X����
	enemyController = new EnemyController();
	particleManager = GameParticleManager::Instance();
	playerObserver = new PlayerObserver();
	bgController = new BackGroundController();

	SetPlayerObserverAdr(playerObserver);

	//�w�i������
	InitBackGroundRoad();
	InitBackGroundField();
	bgController->Init();

	//�p�[�e�B�N��������
	particleManager->Init();

	//�v���C���[������
	playerObserver->Init();

	//�T�E���h������
	Sound::GetInstance()->Create();

	//�G�l�~�[������
	enemyController->Init();

	//��Q��������
	InitRebarOb();

	//�v���t�@�C����GameScene��o�^
	RegisterDebugTimer(GAMESCENE_LABEL);

	//�X�e�[�g������
	currentState = State::Start;
	state = fsm[currentState];
	state->OnStart(this);
}

/**************************************
�I������
***************************************/
void GameScene::Uninit()
{
	//�w�i�I��
	UninitBackGroundRoad();
	UninitBackGroundField();
	bgController->Uninit();

	//�p�[�e�B�N���I��
	particleManager->Uninit();

	//�v���C���[�I��
	playerObserver->Uninit();

	//�G�l�~�[�I��
	enemyController->Uninit();

	//UI�I��
	UninitGameSceneUI();

	//��Q���I��
	UninitRebarOb();

	//�C���X�^���X�폜
	SAFE_DELETE(enemyController);
	SAFE_DELETE(playerObserver);
	SAFE_DELETE(bgController);
	SAFE_DELETE(darkMask);

	//�X�e�[�g�}�V���폜
	for (auto& pair : fsm)
	{
		SAFE_DELETE(pair.second);
	}
	fsm.clear();
}

/**************************************
�X�V����
***************************************/
void GameScene::Update(HWND hWnd)
{
	//�T�E���h�Đ�(�e�X�g�j
	InputSound();

	//�X�e�[�g�X�V����
	int result = state->OnUpdate(this);

	if (result != currentState)
		ChangeState(result);

	//UI�̍X�V
	CountDebugTimer(GAMESCENE_LABEL, "UpdateUI");
	UpdateGameSceneUI(hWnd);
	CountDebugTimer(GAMESCENE_LABEL, "UpdateUI");
}

/**************************************
�`�揈��
***************************************/
void GameScene::Draw()
{

	//�w�i�̕`��
	CountDebugTimer(GAMESCENE_LABEL, "DrawBG");
	//DrawBackGroundRoad();
	//DrawBackGroundField();
	bgController->Draw();
	CountDebugTimer(GAMESCENE_LABEL, "DrawBG");

	//��Q���̕`��
	DrawRebarOb();

	//�Ó]�p�|���S���̕`��
	if (useDarkMask)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

		darkMask->Draw();

		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
	}

	//�v���C���[�̕`��
	CountDebugTimer(GAMESCENE_LABEL, "DrawPlayer");
	playerObserver->Draw();
	CountDebugTimer(GAMESCENE_LABEL, "DrawPlayer");

	//�G�l�~�[�̕`��
	enemyController->Draw();
	enemyController->DrawGuide();

	//�p�[�e�B�N���`��
	CountDebugTimer(GAMESCENE_LABEL, "DrawParticle");
	particleManager->Draw();
	CountDebugTimer(GAMESCENE_LABEL, "DrawParticle");

	//�|�X�g�G�t�F�N�g�`��
	CountDebugTimer(GAMESCENE_LABEL, "DrawpostEffect");
	PostEffectManager::Instance()->Draw();
	CountDebugTimer(GAMESCENE_LABEL, "DrawpostEffect");

	//UI�`��
	DrawGameSceneUI();

	DrawDebugTimer(GAMESCENE_LABEL);
}

/**************************************
�X�e�[�g�J�ڏ���
***************************************/
void GameScene::ChangeState(int next)
{
	if (next < 0 || next >= State::StateMax)
		return;

	currentState = (State)next;
	state = fsm[currentState];
	state->OnStart(this);
}

/**************************************
�S�̍X�V����
***************************************/
void GameScene::UpdateWhole()
{
	//�w�i�I�u�W�F�N�g�̍X�V
	CountDebugTimer(GAMESCENE_LABEL, "UpdateBG");
	UpdateBackGroundRoad();
	UpdateBackGroundField();
	bgController->Update();
	CountDebugTimer(GAMESCENE_LABEL, "UpdateBG");

	//�v���C���[�̍X�V
	CountDebugTimer(GAMESCENE_LABEL, "UpdatePlayer");
	playerObserver->Update();
	CountDebugTimer(GAMESCENE_LABEL, "UpdatePlayer");

	//�G�l�~�[�̍X�V
	enemyController->Update();

	//�p�[�e�B�N���̍X�V
	CountDebugTimer(GAMESCENE_LABEL, "UpdateParticle");
	particleManager->Update();
	CountDebugTimer(GAMESCENE_LABEL, "UpdateParticle");

	//�|�X�g�G�t�F�N�g�̍X�V
	PostEffectManager::Instance()->Update();

	//��Q���̍X�V
	UpdateRebarOb();
}

/**************************************
�S�̕`�揈��
***************************************/
void GameScene::DrawWhole()
{

}