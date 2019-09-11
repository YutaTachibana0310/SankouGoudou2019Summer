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
#include "ScoreManager.h"
#include "PostEffect\SpeedBlurController.h"
#include "BossController.h"
#include "BossUIManager.h"
#include "PostEffect\MonotoneFilter.h"
#include "GameOver.h"

#include "GameStart.h"
#include "GameBattle.h"
#include "GameEnd.h"
#include "GameBomberSequence.h"
#include "GameBossBattle.h"
#include "GameBossStart.h"
#include "GameBossBombSequence.h"
#include "GameFailed.h"

#include "RebarOb.h"
#include <functional>

#include "SoundGameScene.h"

using namespace std;

/**************************************
�}�N����`
***************************************/
#define GAMESCENE_LABEL			("GameScene")
#define COMBOEFFECT_PERIOD		(25)			//���̃R���{�����ɉ��o����������

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
	fsm[State::BossBattle] = new GameBossBattle();
	fsm[State::BossStart] = new GameBossStart();
	fsm[State::BossBombSequence] = new GameBossBombSequence();
	fsm[State::Failed] = new GameFailed();

	//�Ó]�p�|���S���쐬
	darkMask = new Polygon2D();
	darkMask->SetSize((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	darkMask->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f));
	useDarkMask = false;

	gameSceneUIManager = new GameSceneUIManager();

	//UI������
	gameSceneUIManager->Init();

	//���{�^���̈ʒu���烏�[���h���W���v�Z
	std::vector<D3DXVECTOR3> starPositionContainer;
	gameSceneUIManager->GetStarPosition(starPositionContainer);
	LineTrailModel::CalcEdgePosition(starPositionContainer);

	//�C���X�^���X����
	enemyController = new EnemyController();
	particleManager = GameParticleManager::Instance();
	playerObserver = new PlayerObserver();
	bgController = new BackGroundController();
	bossUI = new BossUImanager();
	bossController = new BossController(playerObserver->GetPlayerTransform(), *bossUI);
	gameover = new GameOver();

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

	//�v���t�@�C����GameScene��o�^
	RegisterDebugTimer(GAMESCENE_LABEL);

	//�X�e�[�g������
	currentState = State::Start;
	state = fsm[currentState];
	state->OnStart(this);
	SoundGameScene::SetScene(currentState);

	//�R�[���o�b�N�ݒ�
	currentCombo = 0;
	SetCallbackClearCombo([&]()
	{
		this->OnClearCombo();
	});

	SetCallbackAddCombo([&](int n)
	{
		this->OnAddCombo(n);
	});
	SetGameScneeUIManagerInstance(gameSceneUIManager);

	//�C���v�b�g�R���g���[����UImanager�̃C���X�^���X��n��
	SetInstanceUIManager(gameSceneUIManager);

	//�X�R�A������
	SetCurrentGameScore(0);
	SetCurrentCombo(0);
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

	//�v���C���[�I��
	playerObserver->Uninit();

	//�G�l�~�[�I��
	enemyController->Uninit();

	//UI�I��
	gameSceneUIManager->Uninit();

	//�X�R�A�}�l�[�W���N���A
	ClearScoreManager();

	//�C���X�^���X�폜
	SAFE_DELETE(gameSceneUIManager);
	SAFE_DELETE(enemyController);
	SAFE_DELETE(playerObserver);
	SAFE_DELETE(bgController);
	SAFE_DELETE(darkMask);
	SAFE_DELETE(bossController);
	SAFE_DELETE(bossUI);

	//�p�[�e�B�N���I��
	particleManager->Uninit();

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

	//�X�e�[�g�X�V����
	int result = state->OnUpdate(this);

	if (result != currentState)
		ChangeState(result);
	SoundGameScene::SetScene(result);

	//UI�̍X�V
	CountDebugTimer(GAMESCENE_LABEL, "UpdateUI");
	gameSceneUIManager->SetHPGuage(playerObserver->GetHpPercent());
	gameSceneUIManager->SetBomberStock(playerObserver->GetBomberStockNum(), playerObserver->IsBomberCharging());
	gameSceneUIManager->Update(hWnd);
	bossUI->Update();
	CountDebugTimer(GAMESCENE_LABEL, "UpdateUI");

	BeginDebugWindow("Console");
	if (DebugButton("AddCombo")) SetAddCombo(1);
	if (DebugButton("ResetCombo")) ClearCombo();
	EndDebugWindow("");
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

	//�Ó]�p�|���S���̕`��
	if (useDarkMask)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

		darkMask->Draw();

		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
	}

	//�G�l�~�[�̕`��
	enemyController->Draw();
	enemyController->DrawGuide();

	//�{�X�̕`��
	bossController->Draw();

	//�v���C���[�̕`��
	CountDebugTimer(GAMESCENE_LABEL, "DrawPlayer");
	playerObserver->Draw();
	CountDebugTimer(GAMESCENE_LABEL, "DrawPlayer");

	//�p�[�e�B�N���`��
	CountDebugTimer(GAMESCENE_LABEL, "DrawParticle");
	particleManager->Draw();
	CountDebugTimer(GAMESCENE_LABEL, "DrawParticle");

	//�|�X�g�G�t�F�N�g�`��
	CountDebugTimer(GAMESCENE_LABEL, "DrawpostEffect");
	PostEffectManager::Instance()->Draw();
	CountDebugTimer(GAMESCENE_LABEL, "DrawpostEffect");

	//UI�`��
	gameSceneUIManager->Draw();
	bossUI->Draw();
	playerObserver->DrawInputGuide();

	//�Q�[���I�[�o�[���̃��m�g�[���t�B���^�`��
	if (!playerObserver->IsAlive())
	{
		MonotoneFilter::Instance()->Draw();
		gameover->Draw();
	}

	DrawDebugTimer(GAMESCENE_LABEL);
}

/**************************************
�X�e�[�g�J�ڏ���
***************************************/
void GameScene::ChangeState(int next)
{
	if (next < 0 || next >= State::StateMax)
		return;

	prevState = currentState;
	currentState = (State)next;
	state = fsm[currentState];
	state->OnStart(this);
	SoundGameScene::SetScene(currentState);

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

	//�G�l�~�[�̍X�V
	enemyController->Update();

	//�{�X�̍X�V
	bossController->Update();

	//�v���C���[�̍X�V
	CountDebugTimer(GAMESCENE_LABEL, "UpdatePlayer");
	playerObserver->Update();
	CountDebugTimer(GAMESCENE_LABEL, "UpdatePlayer");

	//�p�[�e�B�N���̍X�V
	CountDebugTimer(GAMESCENE_LABEL, "UpdateParticle");
	particleManager->Update();
	CountDebugTimer(GAMESCENE_LABEL, "UpdateParticle");

	//�|�X�g�G�t�F�N�g�̍X�V
	PostEffectManager::Instance()->Update();
}

/**************************************
�S�̕`�揈��
***************************************/
void GameScene::DrawWhole()
{

}

/**************************************
�R���{���Z�����o
***************************************/
void GameScene::OnAddCombo(int n)
{
	static const float AddPower = 10.0f;
	static const float AddSpeed = -50.0f;

	currentCombo += n;

	if (currentCombo % COMBOEFFECT_PERIOD != 0)
		return;

	SpeedBlurController::Instance()->AddPower(AddPower);
	bgController->AddScrollSpeed(AddSpeed);
	playerObserver->OnStartAccel();
}

/**************************************
�R���{�N���A�����o
***************************************/
void GameScene::OnClearCombo()
{
	static const float InitPower = 0.0f;

	currentCombo = 0;

	SpeedBlurController::Instance()->SetPower(InitPower);
	bgController->InitScroolSpeed();
}

/**************************************
�{���o�[���˔���
***************************************/
bool GameScene::ShouldFireBomber()
{
	return playerObserver->ShouldFireBomber() && enemyController->ExistsAcitveEnemy();
}

/**************************************
�{�X�펞
***************************************/
bool GameScene::ShouldFireBomberOnBossBattle()
{
	//TODO : �{�X���Č�Ƀ{���o�[�𔭎˂ł��Ȃ��悤�ɂ���
	return  playerObserver->ShouldFireBomber();
}
