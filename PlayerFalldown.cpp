//=====================================
//
//�v���C���[�ė�����[PlayerFalldown.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "PlayerFalldown.h"
#include "Framework\Easing.h"
#include "Framework\Vector3.h"
#include "PlayerObserver.h"

/**************************************
�O���[�o���ϐ�
***************************************/

/**************************************
���ꏈ��
***************************************/
void PlayerFalldown::OnStart(Player * entity)
{
	entity->ChangeAnim(PlayerAnimID::FallDown);
	entity->cntFrame = 0;
	initPos = entity->transform.pos;
}

/**************************************
�X�V����
***************************************/
int PlayerFalldown::OnUpdate(Player * entity)
{
	entity->cntFrame++;

	const float FallDuration = 240;
	float t = entity->cntFrame / FallDuration;
	entity->transform.pos = Easing::EaseValue(t, initPos, initPos + Vector3::Down * 300.0f, EaseType::InSine);

	return StateContinuous;
}
