//=====================================
//
//ゲームパーティクルマネージャヘッダ[GameParticleManager.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _GameParticleManager_H_
#define _GameParticleManager_H_

#include "main.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/

/**************************************
プロトタイプ宣言
***************************************/
void InitGameParticleManager(int num);
void UninitGameParticleManager(int num);
void UpdateGameParticleManager(void);
void DrawGameParticleManager(void);

void SetScoreParticle(D3DXVECTOR3 *pos);
void SetPlayerBulletParticle(D3DXVECTOR3 *pPos, bool *pActive, D3DXVECTOR3 *edgeRight, D3DXVECTOR3 *edgeLeft);
void SetPlayerTrailParticle(D3DXVECTOR3 *pPos, bool *pActive);

#endif