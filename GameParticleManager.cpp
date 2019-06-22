//=====================================
//
//�Q�[���p�[�e�B�N���}�l�[�W������[GameParticleManager.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "GameParticleManager.h"

#include <vector>

#include "ScoreParticleController.h"
#include "PlayerBulletParticle.h"

#include "PostEffect\ScreenObject.h"
#include "PostEffect\CrossFilterController.h"

#ifdef _DEBUG
#include "debugWindow.h"
#endif

using namespace std;

/**************************************
�}�N����`
***************************************/
#define GAMEPARTICLE_EFFECT_NAME		"Framework/particle3D.fx"
#define GAMEPARTICLE_PRECOMPILE_NAME	"data/EFFECT/particle3D.cfx"

/**************************************
�\���̒�`
***************************************/

/**************************************
�O���[�o���ϐ�
***************************************/
static LPDIRECT3DVERTEXDECLARATION9 vtxDeclare;
static LPD3DXEFFECT effect;
static LPDIRECT3DINDEXBUFFER9 indexBuff;

//�����_�[�^�[�Q�b�g�֘A
static LPDIRECT3DTEXTURE9 renderTexture;
static LPDIRECT3DSURFACE9 renderSurface;
static D3DVIEWPORT9 viewPort;
static ScreenObject *screenObj;

vector<BaseParticleController*> container;

/**************************************
�v���g�^�C�v�錾
***************************************/
namespace GameParticle
{
	void DrawDebugWindow(void);					//�f�o�b�O�\��
	void CreateRenderTarget(void);				//�����_�[�^�[�Q�b�g�쐬
	void ChangeRenderParameter(void);			//�����_�����O�ݒ�؂�ւ�
	void RestoreRenderParameter(LPDIRECT3DSURFACE9 oldSuf, _D3DVIEWPORT9 oldViewport);			//�����_�����O�ݒ蕜��
}


/**************************************
����������
***************************************/
void InitGameParticleManager(int num)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	container.push_back(new ScoreParticleController());

	//�����_�[�^�[�Q�b�g�쐬
	GameParticle::CreateRenderTarget();

	//�e�p�[�e�B�N��������
	//InitPlayerBulletParticle(0);
	for (auto itr = container.begin(); itr != container.end(); itr++)
	{
		(*itr)->Init();
	}
}

/**************************************
�I������
***************************************/
void UninitGameParticleManager(int num)
{
	//UninitPlayerBulletParticle(0);
	for (auto itr = container.begin(); itr != container.end(); itr++)
	{
		(*itr)->Uninit();
	}

	SAFE_RELEASE(renderSurface);
	SAFE_RELEASE(renderTexture);
	SAFE_DELETE(screenObj);
}

/**************************************
�X�V����
***************************************/
void UpdateGameParticleManager(void)
{
#ifdef _DEBUG
	GameParticle::DrawDebugWindow();
#endif

	//UpdatePlayerBulletParticle();
	for (auto itr = container.begin(); itr != container.end(); itr++)
	{
		(*itr)->Update();
	}
}

/**************************************
�`�揈��
***************************************/
void DrawGameParticleManager(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	////�����_�����O�ݒ�؂�ւ�
	//D3DVIEWPORT9 oldViewport;
	//LPDIRECT3DSURFACE9 oldSuf;
	//pDevice->GetViewport(&oldViewport);
	//pDevice->GetRenderTarget(0, &oldSuf);
	//GameParticle::ChangeRenderParameter();

	BaseParticleController::BeginDraw();

	//�`��
	for (auto itr = container.begin(); itr != container.end(); itr++)
	{
		(*itr)->Draw();
	}

	//DrawPlayerBulletParticle();

	BaseParticleController::EndDraw();

#ifndef _DEBUG	//�N���X�t�B���^��Release�łł̂ݓK�p����
	//�|�X�g�G�t�F�N�g
	CrossFilterController::Instance()->Draw(renderTexture);
#endif // !_DEBUG

	////�S�Ă̌��ʂ����̃����_�[�^�[�Q�b�g�ɕ`��
	//GameParticle::RestoreRenderParameter(oldSuf, oldViewport);
	//screenObj->Draw();

	////�����_�[�X�e�[�g����
	//pDevice->SetRenderState(D3DRS_LIGHTING, true);
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

/**************************************
�����_�[�^�[�Q�b�g�쐬
***************************************/
void GameParticle::CreateRenderTarget()
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
�����_�����O�ݒ�؂�ւ�
***************************************/
void GameParticle::ChangeRenderParameter()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�����_�[�^�[�Q�b�g�؂�ւ�
	pDevice->SetRenderTarget(0, renderSurface);
	pDevice->SetViewport(&viewPort);
	pDevice->Clear(0, 0, D3DCLEAR_TARGET, 0, 0.0f, 0);

	//�r���[�s��A�v���W�F�N�V�����s��A�r���[�t�s����擾
	D3DXMATRIX view, projection, invView;
	pDevice->GetTransform(D3DTS_VIEW, &view);
	pDevice->GetTransform(D3DTS_PROJECTION, &projection);
	D3DXMatrixInverse(&invView, NULL, &view);
	invView._41 = invView._42 = invView._43 = 0.0f;

	//�V�F�[�_�Ɋe�s���ݒ�
	effect->SetMatrix("mtxView", &view);
	effect->SetMatrix("mtxProj", &projection);
	effect->SetMatrix("mtxInvView", &invView);

	//�C���f�b�N�X�o�b�t�@�ƒ��_�錾��ݒ�
	pDevice->SetIndices(indexBuff);
	pDevice->SetVertexDeclaration(vtxDeclare);
}

/**************************************
�����_�����O�ݒ蕜��
***************************************/
void GameParticle::RestoreRenderParameter(LPDIRECT3DSURFACE9 oldSuf, _D3DVIEWPORT9 oldViewport)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderTarget(0, oldSuf);
	pDevice->SetTexture(0, renderTexture);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	pDevice->SetViewport(&oldViewport);
	SAFE_RELEASE(oldSuf);
}

#ifdef _DEBUG
/**************************************
�f�o�b�O�E�B���h�E
***************************************/
void GameParticle::DrawDebugWindow(void)
{
	BeginDebugWindow("GameParticle");
	
	{
		if (DebugButton("ScoreParticle"))
			container[0]->SetEmitter(&D3DXVECTOR3(0.0f, 0.0f, 50.0f));
	}

	{
		static bool active = true;
		static D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 150.0f);
		if (DebugButton("PlayerBulletParticle"))
			SetPlayerBulletParticle(&pos, &active, &D3DXVECTOR3(-100.0f, 0.0f, 0.0f), &D3DXVECTOR3(100.0f, 0.0f, 0.0f));
	}

	//{
	//	DebugDrawTexture(renderTexture, 500.0f, 200.0f);
	//}

	EndDebugWindow("GameParticle");
}
#endif