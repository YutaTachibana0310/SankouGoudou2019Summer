//=====================================
//
//�Q�[���p�[�e�B�N���}�l�[�W���w�b�_[GameParticleManager.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _GameParticleManager_H_
#define _GameParticleManager_H_

#include "main.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/

/**************************************
�v���g�^�C�v�錾
***************************************/
void InitGameParticleManager(int num);
void UninitGameParticleManager(int num);
void UpdateGameParticleManager(void);
void DrawGameParticleManager(void);

void SetScoreParticle(D3DXVECTOR3 *pos);
void SetPlayerBulletParticle(D3DXVECTOR3 *pPos, bool *pActive, D3DXVECTOR3 *edgeRight, D3DXVECTOR3 *edgeLeft);
void SetPlayerTrailParticle(D3DXVECTOR3 *pPos, bool *pActive);

#endif