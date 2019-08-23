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
#include "PlayerBomberParticleController.h"
#include "EnemyWarpHoleController.h"
#include "EnemyBulletTrailController.h"
#include "EnemyBulletEffectController.h"
#include "EnemyBulletChargeController.h"
#include "EnemyBulletFireController.h"
#include "EnemyGuideArrowController.h"
#include "PlayerChargeEffectController.h"
#include "PlayerChargeParticleController.h"
#include "AccelEffectController.h"
#include "BomberFireController.h"
#include "BossChargeEffect.h"
#include "BossHitParticle.h"
#include "ExplosionFire.h"

#include "LineTrailModel.h"

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
	PlayerBomberParticle,
	EnemyWarpHole,
	EnemyBulletTrail,
	EnenyBulletEffect,
	EnemyBulletCharge,
	EnemyBulletFire,
	PlayerCharge,
	PlayerChargeParticle,
	AccelEffect,
	BomberFire,
	BossCharge,
	BossHit,
	BossExplosion,
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
	controllers[PlayerBomberParticle] = new PlayerBomberParticleController();
	controllers[EnemyWarpHole] = new EnemyWarpHoleController();
	controllers[EnemyBulletTrail] = new EnemyBulletTrailController();
	controllers[EnenyBulletEffect] = new EnemyBulletEffectController();
	controllers[EnemyBulletCharge] = new EnemyBulletChargeController();
	controllers[EnemyBulletFire] = new EnemyBulletFireController();
	controllers[PlayerCharge] = new PlayerChargeEffectController();
	controllers[PlayerChargeParticle] = new PlayerChargeParticleController();
	controllers[AccelEffect] = new AccelEffectController();
	controllers[BomberFire] = new BomberFireController();
	controllers[BossCharge] = new BossChargeParticleController();
	controllers[BossHit] = new BossHitParticleController();
	controllers[BossExplosion] = new ExplosionFireController();

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
�{���o�[�p�[�e�B�N���X�V����
***************************************/
void GameParticleManager::UpdateBombParticle()
{
	controllers[BomberFire]->Update();
	controllers[PlayerBomberParticle]->Update();
	controllers[PlayerChargeParticle]->Update();
	controllers[PlayerCharge]->Update();
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
�v���C���[�{���o�[�p�[�e�B�N������
***************************************/
void GameParticleManager::SetPlayerBomberParticle(D3DXVECTOR3 *pPos, bool *pActive)
{
	PlayerBomberParticleController *controller
		= static_cast<PlayerBomberParticleController*>(controllers[PlayerBomberParticle]);

	controller->SetEmitter(pPos, pActive);
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
	controllers[EnemyBulletFire]->SetEmitter(pos);
	return controllers[EnemyBulletTrail]->SetEmitter(pos);
}

/**************************************
�G�l�~�[�o���b�g�����Z�b�g����
***************************************/
void GameParticleManager::SetEnemyBulletExplosion(D3DXVECTOR3 *pos)
{
	controllers[EnemyBulletFire]->SetEmitter(pos);
}

/**************************************
�G�l�~�[�o���b�g�G�t�F�N�g�Z�b�g����
***************************************/
BaseEmitter* GameParticleManager::SetEnemyBulletEffect(LineTrailModel model)
{
	EnemyBulletEffectController *entity = static_cast<EnemyBulletEffectController*>(controllers[EnenyBulletEffect]);
	return entity->SetEmitter(model);
}

/**************************************
�G�l�~�[�o���b�g�`���[�W�Z�b�g����
***************************************/
BaseEmitter* GameParticleManager::SetEnemyBulletCharge(D3DXVECTOR3 *pos)
{
	return controllers[EnemyBulletCharge]->SetEmitter(pos);
}

/**************************************
�v���C���[�`���[�W�G�t�F�N�g�Z�b�g����
***************************************/
void GameParticleManager::SetPlayerCharge(D3DXVECTOR3 *pos)
{
	controllers[PlayerChargeParticle]->SetEmitter(pos);
	controllers[PlayerCharge]->SetEmitter(pos);
}

/**************************************
�����G�t�F�N�g�Z�b�g����
***************************************/
void GameParticleManager::SetAccelEffect(D3DXVECTOR3 *pos)
{
	controllers[AccelEffect]->SetEmitter(pos);
}

/**************************************
�{���o�[���˃G�t�F�N�g�Z�b�g����
***************************************/
void GameParticleManager::SetBomberFire(D3DXVECTOR3* pos)
{
	controllers[BomberFire]->SetEmitter(pos);
}

/**************************************
�{�X�`���[�W�G�t�F�N�g
***************************************/
void GameParticleManager::SetBossCharge(D3DXVECTOR3 *pos)
{
	controllers[BossCharge]->SetEmitter(pos);
}

/**************************************
�{�X�q�b�g�G�t�F�N�g
***************************************/
void GameParticleManager::SetBossHit(D3DXVECTOR3 *pos)
{
	controllers[BossHit]->SetEmitter(pos);
}

/**************************************
�{�X�����G�t�F�N�g
***************************************/
void GameParticleManager::SetBossExplosion(D3DXVECTOR3 *pos)
{
	controllers[BossExplosion]->SetEmitter(pos);
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

	{
		if (DebugButton("PlayerCharge"))
			SetPlayerCharge(&D3DXVECTOR3(50.0f, 50.0f, 50.0f));
	}

	{
		if (DebugButton("Accel"))
			SetAccelEffect(&D3DXVECTOR3(0.0f, 0.0f, 50.0f));
	}

	EndDebugWindow("GameParticle");
}
#endif