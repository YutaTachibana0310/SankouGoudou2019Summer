//=====================================
//
//�Q�[���p�[�e�B�N���}�l�[�W������[GameParticleManager.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "GameParticleManager.h"

#include "ScoreParticleController.h"
#include "PlayerBulletParticleController.h"
#include "PlayerTrailParticleController.h"
#include "EnemyExplosionController.h"
#include "EnemyExplosionFlareController.h"
#include "EnemyWarpHoleController.h"
#include "EnemyBulletTrailController.h"

using namespace std;

/**************************************
�}�N����`
***************************************/
#define GAMEPARTICLE_USE_DEBUG

#ifdef GAMEPARTICLE_USE_DEBUG
#include "debugWindow.h"
#endif

typedef SceneParticleManager Base;

/**************************************
�\���̒�`
***************************************/
enum ParticleController
{
	ScoreParticle,
	PlayerBulletParticle,
	PlayerTrailParticle,
	EnemyExplosion,
	EnemyExplosionFlare,
	EnemyWarpHole,
	EnemyBulletTrail,
	ControllerMax
};

/**************************************
����������
***************************************/
void GameParticleManager::Init()
{
	Base::Init();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�e�R���g���[���𐶐�
	controllers.resize(ControllerMax);
	controllers[ScoreParticle] = new ScoreParticleController();
	controllers[PlayerBulletParticle] = new PlayerBulletParticleController();
	controllers[PlayerTrailParticle] = new PlayerTrailParticleController();
	controllers[EnemyExplosion] = new EnemyExplosionController();
	controllers[EnemyExplosionFlare] = new EnemyExplosionFlareController();
	controllers[EnemyWarpHole] = new EnemyWarpHoleController();
	controllers[EnemyBulletTrail] = new EnemyBulletTrailController();

	//�e�p�[�e�B�N��������
	for (auto& controller : controllers)
	{
		controller->Init();
	}
}

/**************************************
�X�V����
***************************************/
void GameParticleManager::Update(void)
{
#ifdef GAMEPARTICLE_USE_DEBUG
	DrawDebugWindow();
#endif

	Base::Update();
}

/**************************************
�X�R�A�p�[�e�B�N����������
***************************************/
void GameParticleManager::SetScoreParticle(D3DXVECTOR3 *pos)
{
	controllers[ScoreParticle]->SetEmitter(pos);
}

/**************************************
�v���C���[�o���b�g�Z�b�g����
***************************************/
void GameParticleManager::SetPlayerBulletParticle(D3DXVECTOR3 *pPos, bool *pActive, D3DXVECTOR3 *edgeRight, D3DXVECTOR3 *edgeLeft)
{
	PlayerBulletParticleController *controller
		= static_cast<PlayerBulletParticleController*>(controllers[PlayerBulletParticle]);

	controller->SetEmitter(pPos, pActive, edgeRight, edgeLeft);
}

/**************************************
�v���C���[�g���C���p�[�e�B�N������
***************************************/
void GameParticleManager::SetPlayerTrailParticle(D3DXVECTOR3 *pPos, bool *pActive)
{
	PlayerTrailParticleController *controller =
		static_cast<PlayerTrailParticleController*>(controllers[PlayerTrailParticle]);

	controller->SetEmitter(pPos, pActive);
}

/**************************************
�G�l�~�[�G�N�X�v���[�W��������
***************************************/
void GameParticleManager::SetEnemyExplosion(D3DXVECTOR3 *pos)
{
	controllers[EnemyExplosion]->SetEmitter(pos);
	controllers[EnemyExplosionFlare]->SetEmitter(pos);
}

/**************************************
�G�l�~�[���[�v�z�[������
***************************************/
void GameParticleManager::SetEnemyWarpHole(D3DXVECTOR3 *pos)
{
	controllers[EnemyWarpHole]->SetEmitter(pos);
}

/**************************************
�G�l�~�[�o���b�g�g���C���Z�b�g����
***************************************/
BaseEmitter* GameParticleManager::SetEnemyBulletTrail(D3DXVECTOR3 *pos)
{
	return controllers[EnemyBulletTrail]->SetEmitter(pos);
}

#ifdef GAMEPARTICLE_USE_DEBUG
/**************************************
�f�o�b�O�E�B���h�E
***************************************/
void GameParticleManager::DrawDebugWindow(void)
{
	BeginDebugWindow("GameParticle");

	{
		if (DebugButton("ScoreParticle"))
			controllers[0]->SetEmitter(&D3DXVECTOR3(0.0f, 0.0f, 50.0f));
	}

	{
		if (DebugButton("EnemyExplosion"))
			SetEnemyExplosion(&D3DXVECTOR3(0.0f, 0.0f, 250.0f));
	}
	EndDebugWindow("GameParticle");
}
#endif