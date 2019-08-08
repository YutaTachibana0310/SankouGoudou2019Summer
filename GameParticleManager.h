//=====================================
//
//ゲームパーティクルマネージャヘッダ[GameParticleManager.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _GameParticleManager_H_
#define _GameParticleManager_H_

#include "main.h"
#include "Framework\SceneParticleManager.h"
#include "Framework\BaseSingleton.h"

/**************************************
マクロ定義
***************************************/
#define GAMEPARTICLE_USE_DEBUG

/**************************************
前方宣言
***************************************/
class LineTrailModel;

/**************************************
クラス定義
***************************************/
class GameParticleManager :
	public SceneParticleManager, 
	public BaseSingleton<GameParticleManager>
{
public:
	friend class BaseSingleton<GameParticleManager>;

	void Init() override;
	void Update() override;
	void UpdateBombParticle();

	void SetScoreParticle(D3DXVECTOR3 *pos);
	void SetPlayerBulletParticle(D3DXVECTOR3 *pPos, bool *pActive, D3DXVECTOR3 *edgeRight, D3DXVECTOR3 *edgeLeft);
	void SetPlayerTrailParticle(D3DXVECTOR3 *pPos, bool *pActive);
	void SetEnemyExplosion(D3DXVECTOR3 *pPos);
	void SetEnemyWarpHole(D3DXVECTOR3 *pPos);
	BaseEmitter* SetEnemyBulletTrail(D3DXVECTOR3 *pPos);
	void SetEnemyBulletEffect(LineTrailModel model);
	BaseEmitter* SetEnemyBulletCharge(D3DXVECTOR3 *pos);
	void SetPlayerCharge(D3DXVECTOR3 *pos);
	void SetAccelEffect(D3DXVECTOR3 *pos);
	void SetEnemyBulletExplosion(D3DXVECTOR3 *pos);

private:
	GameParticleManager() {}
	~GameParticleManager() {}

#ifdef GAMEPARTICLE_USE_DEBUG
	void DrawDebugWindow();
#endif

};


#endif