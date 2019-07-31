//=====================================
//
//�G�l�~�[�K�C�h�A���[����[EnemyGuideArrow.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "EnemyGuideArrow.h"
#include "Framework\Easing.h"

/**************************************
�}�N����`
***************************************/
#define ENEMYGUIDEARROW_LIFEFRAME		(60)
#define ENEMYGUIDEARROW_DURATION		(30)

/**************************************
EnemyGuideArrow����������
***************************************/
void EnemyGuideArrow::Init()
{
	cntFrame = 0;
	active = true;

	transform.scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	lifeFrame = ENEMYGUIDEARROW_LIFEFRAME;
}

/**************************************
EnemyGuideArrow�X�V����
***************************************/
void EnemyGuideArrow::Update()
{
	static const float InitScale = 1.0f, EndScale = 0.0f;
	cntFrame++;

	float t = (float)cntFrame / lifeFrame;
	transform.scale = Easing<float>::GetEasingValue(t, &InitScale, &EndScale, EasingType::InExponential) * D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	if (cntFrame == lifeFrame)
		active = false;
}

/**************************************
EnemyGuideArrow����������
***************************************/
void EnemyGuideArrowEmitter::Init()
{
	cntFrame = 0;
	active = true;
	duration = ENEMYGUIDEARROW_DURATION;
}

/**************************************
EnemyGuideArrow����������
***************************************/
void EnemyGuideArrowEmitter::Update()
{
	cntFrame++;

	float t = (float)cntFrame / duration;
	transform.pos = Easing<D3DXVECTOR3>::GetEasingValue(t, &start, &end, EasingType::Linear);

	if (cntFrame == duration)
		active = false;
}