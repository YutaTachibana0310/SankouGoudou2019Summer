#pragma once
//=====================================
//
//�v���C���[�o���b�g�p�[�e�B�N���w�b�_[PlayerBulletParticle.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _PLAYERBULLETPARTICLE_H_
#define _PLAYERBULLETPARTICLE_H_

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
void InitPlayerBulletParticle(int num);
void UninitPlayerBulletParticle(int num);
void UpdatePlayerBulletParticle(void);
void DrawPlayerBulletParticle(void);
void SetPlayerBulletParticle(D3DXVECTOR3 *pPos, bool *pActive, const D3DXVECTOR3 *edgeRight, const D3DXVECTOR3 *edgeLeft);

#endif