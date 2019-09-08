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

	//PlayerController��PlayerObserver���Z�b�g
	SetPlayerObserverAdr(playerObserver);

	//�C���v�b�g�R���g���[����UIManager�̃C���X�^���X��n��
	SetInstanceUIManager(container);
	
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

	bg->Update();
	playerObserver->Update();

	controller->Update();

	container->Update(hWnd);

	GameParticleManager::Instance()->Update();
}

/**************************************
�`�揈��
***************************************/
void TutorialScene::Draw()
{
	bg->Draw();
	playerObserver->Draw();

	GameParticleManager::Instance()->Draw();

	container->Draw();

	controller->Draw();
}
