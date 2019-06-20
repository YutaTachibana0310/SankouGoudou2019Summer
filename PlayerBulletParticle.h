#pragma once
//=====================================
//
//プレイヤーバレットパーティクルヘッダ[PlayerBulletParticle.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _PLAYERBULLETPARTICLE_H_
#define _PLAYERBULLETPARTICLE_H_

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
void InitPlayerBulletParticle(int num);
void UninitPlayerBulletParticle(int num);
void UpdatePlayerBulletParticle(void);
void DrawPlayerBulletParticle(void);
void SetPlayerBulletParticle(D3DXVECTOR3 *pPos, bool *pActive, const D3DXVECTOR3 *edgeRight, const D3DXVECTOR3 *edgeLeft);

#endif