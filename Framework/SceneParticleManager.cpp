//=====================================
//
//�V�[���p�[�e�B�N���}�l�[�W������[SceneParticleManager.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "SceneParticleManager.h"
#include "../PostEffect/CrossFilterController.h"
#include "../debugTimer.h"

/**************************************
�}�N����`
***************************************/
#define SCENEMPARTICLEMANAGER_LABEL		"ParticleManager"

/**************************************
�R���X�g���N�^
***************************************/
SceneParticleManager::SceneParticleManager()
{
	RegisterDebugTimer(SCENEMPARTICLEMANAGER_LABEL);
}

/**************************************
�f�X�g���N�^
***************************************/
SceneParticleManager::~SceneParticleManager()
{

}

/**************************************
����������
***************************************/
void SceneParticleManager::Init()
{
	//�V���O���g�����̂��߁A�����Ń��\�[�X���쐬
	if (!initialized)
	{
		CreateRenderTarget();
		initialized = true;
	}
}

/**************************************
�I������
***************************************/
void SceneParticleManager::Uninit()
{
	for (auto& controller : controllers)
	{
		controller->Uninit();
	}

	//�V���O���g���̂��߂����Ń��\�[�X���
	SAFE_RELEASE(renderSurface);
	SAFE_RELEASE(renderTexture);
	SAFE_DELETE(screenObj);

	for (auto& controller : controllers)
	{
		SAFE_DELETE(controller);
	}
	controllers.clear();

	initialized = false;
}

/**************************************
�X�V����
***************************************/
void SceneParticleManager::Update()
{
	CountDebugTimer(SCENEMPARTICLEMANAGER_LABEL, "Update");
	for (auto& controller : controllers)
	{
		controller->Update();
	}
	CountDebugTimer(SCENEMPARTICLEMANAGER_LABEL, "Update");
}

/**************************************
�`�揈��
***************************************/
void SceneParticleManager::Draw()
{
	//�����_�[�p�����[�^�؂�ւ�
	ChangeRenderParameter();

	//�C���X�^���V���O�`��J�n
	BaseParticleController::BeginDraw();

	//�`��
	CountDebugTimer(SCENEMPARTICLEMANAGER_LABEL, "Draw");
	bool isDrewd = false;
	for (auto& controller : controllers)
	{
		isDrewd |= controller->Draw();
	}
	CountDebugTimer(SCENEMPARTICLEMANAGER_LABEL, "Draw");

	//�C���X�^���V���O�`��I��
	BaseParticleController::EndDraw();

	//�����[�X�ł̂݃N���X�t�B���^��K�p����
#ifndef _DEBUG	
	CountDebugTimer(SCENEMPARTICLEMANAGER_LABEL, "PostEffect");
	if (isDrewd)
		CrossFilterController::Instance()->Draw(renderTexture);
	CountDebugTimer(SCENEMPARTICLEMANAGER_LABEL, "PostEffect");
#endif

	//���ׂĂ̌��ʂ����̃����_�[�^�[�Q�b�g�ɕ`��
	CountDebugTimer(SCENEMPARTICLEMANAGER_LABEL, "Render");
	RestoreRenderParameter();
	screenObj->Draw();
	CountDebugTimer(SCENEMPARTICLEMANAGER_LABEL, "Render");

	//�����_�[�X�e�[�g����
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->SetRenderState(D3DRS_LIGHTING, true);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	DrawDebugTimer(SCENEMPARTICLEMANAGER_LABEL);

}

/**************************************
�����_�[�^�[�Q�b�g�쐬����
***************************************/
void SceneParticleManager::CreateRenderTarget()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�����_�[�^�[�Q�b�g�쐬
	pDevice->CreateTexture(SCREEN_WIDTH,
		SCREEN_HEIGHT,
		1,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_X8R8G8B8,
		D3DPOOL_DEFAULT,
		&renderTexture,
		0);

	//�T�[�t�F�C�X�擾
	renderTexture->GetSurfaceLevel(0, &renderSurface);

	//�r���[�|�[�g�쐬
	pDevice->GetViewport(&viewPort);
	viewPort.Width = SCREEN_WIDTH;
	viewPort.Height = SCREEN_HEIGHT;

	//�`��p�X�N���[���I�u�W�F�N�g�쐬
	screenObj = new ScreenObject();
}

/**************************************
�����_�[�p�����[�^�ύX����
***************************************/
void SceneParticleManager::ChangeRenderParameter()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�����_�[�^�[�Q�b�g�ƃr���[�|�[�g���L���b�V��
	pDevice->GetRenderTarget(0, &oldSuf);
	pDevice->GetViewport(&oldViewport);

	//�����_�[�^�[�Q�b�g�؂�ւ�
	pDevice->SetRenderTarget(0, renderSurface);
	pDevice->SetViewport(&viewPort);
	pDevice->Clear(0, 0, D3DCLEAR_TARGET, 0, 0.0f, 0);
}

/**************************************
�����_�[�p�����[�^��������
***************************************/
void SceneParticleManager::RestoreRenderParameter()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderTarget(0, oldSuf);
	pDevice->SetTexture(0, renderTexture);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	pDevice->SetViewport(&oldViewport);
	SAFE_RELEASE(oldSuf);
}