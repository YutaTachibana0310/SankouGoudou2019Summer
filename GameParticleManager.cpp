//=====================================
//
//�Q�[���p�[�e�B�N���}�l�[�W������[GameParticleManager.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "GameParticleManager.h"

#include <vector>

#include "ScoreParticleController.h"
#include "PlayerBulletParticleController.h"
#include "PlayerTrailParticleController.h"
#include "EnemyExplosionController.h"

#include "PostEffect\ScreenObject.h"
#include "PostEffect\CrossFilterController.h"

using namespace std;

/**************************************
�}�N����`
***************************************/
#define GAMEPARTICLE_USE_DEBUG

#ifdef GAMEPARTICLE_USE_DEBUG
#include "debugWindow.h"
#endif

/**************************************
�\���̒�`
***************************************/
enum ParticleController
{
	ScoreParticle,
	PlayerBulletParticle,
	PlayerTrailParticle,
	EnemyExplosion,
	ControllerMax
};

/**************************************
�O���[�o���ϐ�
***************************************/
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

	//�e�R���g���[���𐶐�
	container.resize(ControllerMax);
	container[ScoreParticle] = new ScoreParticleController();
	container[PlayerBulletParticle] = new PlayerBulletParticleController();
	container[PlayerTrailParticle] = new PlayerTrailParticleController();
	container[EnemyExplosion] = new EnemyExplosionController();

	//�����_�[�^�[�Q�b�g�쐬
	GameParticle::CreateRenderTarget();

	//�e�p�[�e�B�N��������
	for (BaseParticleController *itr : container)
	{
		itr->Init();
	}
}

/**************************************
�I������
***************************************/
void UninitGameParticleManager(int num)
{
	for (BaseParticleController *itr : container)
	{
		itr->Uninit();
	}

	vector<BaseParticleController*>().swap(container);

	SAFE_RELEASE(renderSurface);
	SAFE_RELEASE(renderTexture);
	SAFE_DELETE(screenObj);
}

/**************************************
�X�V����
***************************************/
void UpdateGameParticleManager(void)
{
#ifdef GAMEPARTICLE_USE_DEBUG
	GameParticle::DrawDebugWindow();
#endif

	for (BaseParticleController *itr : container)
	{
		itr->Update();
	}
}

/**************************************
�`�揈��
***************************************/
void DrawGameParticleManager(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	////�����_�����O�ݒ�؂�ւ�
	D3DVIEWPORT9 oldViewport;
	LPDIRECT3DSURFACE9 oldSuf;
	pDevice->GetViewport(&oldViewport);
	pDevice->GetRenderTarget(0, &oldSuf);
	GameParticle::ChangeRenderParameter();

	BaseParticleController::BeginDraw();

	//�`��
	bool isDrewd = false;
	for (auto itr = container.begin(); itr != container.end(); itr++)
	{
		isDrewd |= (*itr)->Draw();
	}

	BaseParticleController::EndDraw();

#ifndef _DEBUG	//�N���X�t�B���^��Release�łł̂ݓK�p����
	//�|�X�g�G�t�F�N�g
	if(isDrewd)
		CrossFilterController::Instance()->Draw(renderTexture);
#endif // !_DEBUG

	////�S�Ă̌��ʂ����̃����_�[�^�[�Q�b�g�ɕ`��
	GameParticle::RestoreRenderParameter(oldSuf, oldViewport);
	screenObj->Draw();

	//�����_�[�X�e�[�g����
	pDevice->SetRenderState(D3DRS_LIGHTING, true);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

/**************************************
�X�R�A�p�[�e�B�N����������
***************************************/
void SetScoreParticle(D3DXVECTOR3 *pos)
{
	container[ScoreParticle]->SetEmitter(pos);
}

/**************************************
�X�R�A�p�[�e�B�N����������
***************************************/

/**************************************
�v���C���[�o���b�g�Z�b�g����
***************************************/
void SetPlayerBulletParticle(D3DXVECTOR3 *pPos, bool *pActive, D3DXVECTOR3 *edgeRight, D3DXVECTOR3 *edgeLeft)
{
	PlayerBulletParticleController *controller
		= static_cast<PlayerBulletParticleController*>(container[PlayerBulletParticle]);

	controller->SetEmitter(pPos, pActive, edgeRight, edgeLeft);
}

/**************************************
�v���C���[�g���C���p�[�e�B�N������
***************************************/
void SetPlayerTrailParticle(D3DXVECTOR3 *pPos, bool *pActive)
{
	PlayerTrailParticleController *controller =
		static_cast<PlayerTrailParticleController*>(container[PlayerTrailParticle]);

	controller->SetEmitter(pPos, pActive);
}

/**************************************
�G�l�~�[�G�N�X�v���[�W��������
***************************************/
void SetEnemyExplosion(D3DXVECTOR3 *pos)
{
	EnemyExplosionController *controller =
		static_cast<EnemyExplosionController*>(container[EnemyExplosion]);

	controller->SetEmitter(pos);
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

#ifdef GAMEPARTICLE_USE_DEBUG
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
		if (DebugButton("EnemyExplosion"))
			container[EnemyExplosion]->SetEmitter(&D3DXVECTOR3(0.0f, 0.0f, 100.0f));
	}
	EndDebugWindow("GameParticle");
}
#endif