//=====================================
//
//�G�l�~�[�G�N�X�v���[�W�����t���A�w�b�_[EnemyExplosionFlare.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _ENEMYEXPLOSIONFLARE_H_
#define _ENEMYEXPLOSIONFLARE_H_

#include "main.h"
#include "Framework\BaseParticle.h"
#include "Framework\BaseEmitter.h"

/**************************************
�}�N����`
***************************************/

/**************************************
EnemyExplosionFlare�N���X
***************************************/
class EnemyExplosionFlare : public BaseParticle
{
public:
	void Init();
	void Update();

private:
	D3DXVECTOR3 initMoveDir;
	D3DXVECTOR3 initScale;
	float speed;
};

/**************************************
EnemyExplosionFlare�N���X
***************************************/
class EnemyExplosionFlareEmitter : public BaseEmitter
{
public:
	void Init();
	void Update();
};

#endif