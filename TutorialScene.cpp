//=====================================
//
//TutorialScene.cpp
//�@�\:�`���[�g���A���V�[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "TutorialScene.h"
#include "TutorialBG.h"
#include "GameSceneUIManager.h"
#include "PlayerObserver.h"
#include "PlayerController.h"
#include "InputController.h"
#include "GameParticleManager.h"
#include "TutorialController.h"
#include "TutorialEnemyController.h"
#include "ScoreManager.h"

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
����������
***************************************/
void TutorialScene::Init()
{
	//UI�C���X�^���X�쐬
	container = new GameSceneUIManager();

	//���{�^���̈ʒu���烏�[���h���W���v�Z
	std::vector<D3DXVECTOR3> starPositionContainer;
	container->GetStarPosition(starPositionContainer);
	LineTrailModel::CalcEdgePosition(starPositionContainer);

	//���̃C���X�^���X�쐬
	bg = new TutorialBG();
	playerObserver = new PlayerObserver();
	controller = new TutorialController();
	enemyController = new TutorialEnemyController();

	//PlayerController��PlayerObserver���Z�b�g
	SetPlayerObserverAdr(playerObserver);

	//�C���v�b�g�R���g���[����UIManager�̃C���X�^���X��n��
	SetInstanceUIManager(container);

	//�X�R�A�}�l�[�W���ɃC���X�^���X��n��
	SetScoreIntance(container->score);
	SetGameScneeUIManagerInstance(container);
	
	//�t�H�O��L����
	FLOAT StartPos = 10000;
	FLOAT EndPos = 50000;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->SetRenderState(D3DRS_FOGENABLE, true);
	pDevice->SetRenderState(D3DRS_FOGCOLOR, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	pDevice->SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_NONE);
	pDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);
	pDevice->SetRenderState(D3DRS_FOGSTART, *(DWORD*)(&StartPos));
	pDevice->SetRenderState(D3DRS_FOGEND, *(DWORD*)(&EndPos));

	//����������
	GameParticleManager::Instance()->Init();
	playerObserver->Init();
}

/**************************************
�I������
***************************************/
void TutorialScene::Uninit()
{
	//�C���X�^���X�폜
	SAFE_DELETE(bg);
	SAFE_DELETE(container);
	SAFE_DELETE(controller);
	SAFE_DELETE(enemyController);

	//�t�H�O�𖳌���
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	if(pDevice != NULL)
		pDevice->SetRenderState(D3DRS_FOGENABLE, false);
}

/**************************************
�X�V����
***************************************/
void TutorialScene::Update(HWND hWnd)
{
	//���͊m�F
	playerObserver->CheckInput();

	//�e�I�u�W�F�N�g�X�V
	bg->Update();
	playerObserver->Update();
	enemyController->Update();

	//�`���[�g���A���K�C�h�X�V
	controller->Update();

	//UI�X�V
	container->Update(hWnd);

	//�p�[�e�B�N���X�V
	GameParticleManager::Instance()->Update();

	//�Փ˔���
	TrailCollider::UpdateCollision();
	BoxCollider3D::UpdateCollision();
}

/**************************************
�`�揈��
***************************************/
void TutorialScene::Draw()
{
	bg->Draw();
	playerObserver->Draw();
	enemyController->Draw();

	GameParticleManager::Instance()->Draw();

	container->Draw();

	controller->Draw();
}
