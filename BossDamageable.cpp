//=====================================
//
//�{�X�_���[�W�G�C�u������[BossDamageable.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "BossDamageable.h"

/**************************************
�}�N����`
***************************************/

/**************************************
���ꏈ��
***************************************/
void BossDamageable::OnStart(BossEnemyModel* entity)
{
	cntFrame = 0;
	entity->SetCollider();
}

/**************************************
�X�V����
***************************************/
int BossDamageable::OnUpdate(BossEnemyModel* entity)
{
	return 0;
}
