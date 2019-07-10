//=====================================
//
//テンプレートヘッダ[SceneParticleManager.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _SCENEPARTICLEMANAGER_H_
#define _SCENEPARTICLEMANAGER_H_

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
void InitSceneParticleManager(int num);
void UninitSceneParticleManager(int num);
void UpdateSceneParticleManager(void);
void DrawSceneParticleManager(void);

#endif