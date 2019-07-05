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
#include "Framework\Singleton.h"

/**************************************
マクロ定義
***************************************/
#define GAMEPARTICLE_USE_DEBUG

/**************************************
クラス定義
***************************************/
class GameParticleManager : public SceneParticleManager
{
public:
	void Init();
	void Update();

	void SetScoreParticle(D3DXVECTOR3 *pos);
	void SetPlayerBulletParticle(D3DXVECTOR3 *pPos, bool *pActive, D3DXVECTOR3 *edgeRight, D3DXVECTOR3 *edgeLeft);
	void SetPlayerTrailParticle(D3DXVECTOR3 *pPos, bool *pActive);
	void SetEnemyExplosion(D3DXVECTOR3 *pPos);

private:

#ifdef GAMEPARTICLE_USE_DEBUG
	void DrawDebugWindow();
#endif

};


#endif