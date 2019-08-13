//=====================================
//
//ゲームパーティクルマネージャ処理[GameParticleManager.cpp]
//Author:GP12B332 21 立花雄太
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

#include "LineTrailModel.h"

using namespace std;

/**************************************
マクロ定義
***************************************/
#define GAMEPARTICLE_USE_DEBUG

#ifdef GAMEPARTICLE_USE_DEBUG
#include "debugWindow.h"
#endif

typedef SceneParticleManager Base;

/**************************************
構造体定義
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
	ControllerMax
};

/**************************************
初期化処理
***************************************/
void GameParticleManager::Init()
{
	Base::Init();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//各コントローラを生成
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

	//各パーティクル初期化
	for (auto& controller : controllers)
	{
		controller->Init();
	}
}

/**************************************
更新処理
***************************************/
void GameParticleManager::Update(void)
{
#ifdef GAMEPARTICLE_USE_DEBUG
	DrawDebugWindow();
#endif

	Base::Update();
}

/**************************************
ボンバーパーティクル更新処理
***************************************/
void GameParticleManager::UpdateBombParticle()
{
	controllers[PlayerBomberParticle]->Update();
	controllers[PlayerChargeParticle]->Update();
	controllers[PlayerCharge]->Update();
}

/**************************************
スコアパーティクル発生処理
***************************************/
void GameParticleManager::SetScoreParticle(D3DXVECTOR3 *pos)
{
	controllers[ScoreParticle]->SetEmitter(pos);
}

/**************************************
プレイヤーバレットセット処理
***************************************/
void GameParticleManager::SetPlayerBulletParticle(D3DXVECTOR3 *pPos, bool *pActive, D3DXVECTOR3 *edgeRight, D3DXVECTOR3 *edgeLeft)
{
	PlayerBulletParticleController *controller
		= static_cast<PlayerBulletParticleController*>(controllers[PlayerBulletParticle]);

	controller->SetEmitter(pPos, pActive, edgeRight, edgeLeft);
}

/**************************************
プレイヤートレイルパーティクル処理
***************************************/
void GameParticleManager::SetPlayerTrailParticle(D3DXVECTOR3 *pPos, bool *pActive)
{
	PlayerTrailParticleController *controller =
		static_cast<PlayerTrailParticleController*>(controllers[PlayerTrailParticle]);

	controller->SetEmitter(pPos, pActive);
}

/**************************************
エネミーエクスプロージョン処理
***************************************/
void GameParticleManager::SetEnemyExplosion(D3DXVECTOR3 *pos)
{
	controllers[EnemyExplosion]->SetEmitter(pos);
	controllers[EnemyExplosionFlare]->SetEmitter(pos);
}

/**************************************
プレイヤーボンバーパーティクル処理
***************************************/
void GameParticleManager::SetPlayerBomberParticle(D3DXVECTOR3 *pPos, bool *pActive)
{
	PlayerBomberParticleController *controller
		= static_cast<PlayerBomberParticleController*>(controllers[PlayerBomberParticle]);

	controller->SetEmitter(pPos, pActive);
}

/**************************************
エネミーワープホール処理
***************************************/
void GameParticleManager::SetEnemyWarpHole(D3DXVECTOR3 *pos)
{
	controllers[EnemyWarpHole]->SetEmitter(pos);
}

/**************************************
エネミーバレットトレイルセット処理
***************************************/
BaseEmitter* GameParticleManager::SetEnemyBulletTrail(D3DXVECTOR3 *pos)
{
	controllers[EnemyBulletFire]->SetEmitter(pos);
	return controllers[EnemyBulletTrail]->SetEmitter(pos);
}

/**************************************
エネミーバレット爆発セット処理
***************************************/
void GameParticleManager::SetEnemyBulletExplosion(D3DXVECTOR3 *pos)
{
	controllers[EnemyBulletFire]->SetEmitter(pos);
}

/**************************************
エネミーバレットエフェクトセット処理
***************************************/
BaseEmitter* GameParticleManager::SetEnemyBulletEffect(LineTrailModel model)
{
	EnemyBulletEffectController *entity = static_cast<EnemyBulletEffectController*>(controllers[EnenyBulletEffect]);
	return entity->SetEmitter(model);
}

/**************************************
エネミーバレットチャージセット処理
***************************************/
BaseEmitter* GameParticleManager::SetEnemyBulletCharge(D3DXVECTOR3 *pos)
{
	return controllers[EnemyBulletCharge]->SetEmitter(pos);
}

/**************************************
プレイヤーチャージエフェクトセット処理
***************************************/
void GameParticleManager::SetPlayerCharge(D3DXVECTOR3 *pos)
{
	controllers[PlayerChargeParticle]->SetEmitter(pos);
	controllers[PlayerCharge]->SetEmitter(pos);
}

/**************************************
加速エフェクトセット処理
***************************************/
void GameParticleManager::SetAccelEffect(D3DXVECTOR3 *pos)
{
	controllers[AccelEffect]->SetEmitter(pos);
}

#ifdef GAMEPARTICLE_USE_DEBUG
/**************************************
デバッグウィンドウ
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