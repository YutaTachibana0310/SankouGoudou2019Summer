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
#include "BackGroundCity.h"
#include "BackGroundRoad.h"
#include "BackGroundField.h"
#include "SkyBox.h"
#include "GameParticleManager.h"
#include "sound.h"
#include "EnemyController.h"
#include "masktex.h"

#include "GameStart.h"
#include "GameBattle.h"
#include "GameEnd.h"

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

	//UI������
	InitGameSceneUI();

	//���{�^���̈ʒu���烏�[���h���W���v�Z
	LineTrailModel::CalcEdgePosition();

	//�C���X�^���X����
	enemyController = new EnemyController();
	particleManager = GameParticleManager::Instance();
	playerObserver = new PlayerObserver();

	SetPlayerObserverAdr(playerObserver);

	//�w�i������
	InitSkyBox(0);
	InitBackGroundCity(0);
	InitBackGroundRoad();
	InitBackGroundField();

	//�p�[�e�B�N��������
	particleManager->Init();

	//�v���C���[������
	playerObserver->Init();

	//�T�E���h������
	Sound::GetInstance()->Create();

	//�G�l�~�[������
	enemyController->Init();

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
	UninitSkyBox(0);
	UninitBackGroundCity(0);
	UninitBackGroundRoad();
	UninitBackGroundField();

	//�p�[�e�B�N���I��
	particleManager->Uninit();

	//�v���C���[�I��
	playerObserver->Uninit();

	//�G�l�~�[�I��
	enemyController->Uninit();

	//UI�I��
	UninitGameSceneUI();

	//�C���X�^���X�폜
	SAFE_DELETE(enemyController);
	SAFE_DELETE(playerObserver);

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

	//�w�i�I�u�W�F�N�g�̍X�V
	CountDebugTimer(GAMESCENE_LABEL, "UpdateBG");
	UpdateSkyBox();
	UpdateBackGroundCity();
	UpdateBackGroundRoad();
	UpdateBackGroundField();
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

	//UI�̍X�V
	CountDebugTimer(GAMESCENE_LABEL, "UpdateUI");
	UpdateGameSceneUI(hWnd);
	CountDebugTimer(GAMESCENE_LABEL, "UpdateUI");

	//�|�X�g�G�t�F�N�g�̍X�V
	PostEffectManager::Instance()->Update();

	//�J�ڏ���
	if (result != STATE_CONTINUOUS)
		ChangeState(result);
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
	playerObserver->Draw();
	CountDebugTimer(GAMESCENE_LABEL, "DrawPlayer");

	//�G�l�~�[�̕`��
	enemyController->Draw();

	//�|�X�g�G�t�F�N�g�`��
	CountDebugTimer(GAMESCENE_LABEL, "DrawpostEffect");
	PostEffectManager::Instance()->Draw();
	CountDebugTimer(GAMESCENE_LABEL, "DrawpostEffect");

	//�p�[�e�B�N���`��
	CountDebugTimer(GAMESCENE_LABEL, "DrawParticle");
	particleManager->Draw();
	CountDebugTimer(GAMESCENE_LABEL, "DrawParticle");

	//UI�`��
	DrawGameSceneUI();

	DrawDebugTimer(GAMESCENE_LABEL);
}

/**************************************
�X�e�[�g�J�ڏ���
***************************************/
void GameScene::ChangeState(int resultUpdate)
{
	switch (currentState)
	{
	case GameScene::State::Idle:

		break;

	case GameScene::State::Start:
		currentState = State::Battle;
		state = fsm[currentState];
		state->OnStart(this);
		break;

	case GameScene::State::Battle:
		currentState = State::End;
		Sound::GetInstance()->playsound = true;
		state = fsm[currentState];
		state->OnStart(this);
		break;

	case GameScene::State::End:
		SceneChangeFlag(true, Scene::SceneResult);
		break;

	default:
		break;
	}
}
