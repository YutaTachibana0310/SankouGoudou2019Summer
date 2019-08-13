//=====================================
//
//�G�l�~�[�K�C�h�A���[����[EnemyGuideArrow.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "EnemyGuideArrow.h"
#include "Framework\Easing.h"
#include "Framework\ResourceManager.h"

/**************************************
�}�N����`
***************************************/
#define ENEMYGUIDEARROW_LIFEFRAME		(30)
#define ENEMYGUIDEARROW_INTERVAL		(1)

#define ENEMYGUIDEARROW_BASE_VECTOR		(&D3DXVECTOR3(0.0f, 1.0f, 0.0f))

/**************************************
EnemyGuideArrow�R���X�g���N�^
***************************************/
EnemyGuideArrow::EnemyGuideArrow()
{
	ResourceManager::Instance()->GetPolygon("EnemyGuideArrow", &polygon);
	cntFrame = 0;
	active = false;
}

/**************************************
EnemyGuideArrow�f�X�g���N�^
***************************************/
EnemyGuideArrow::~EnemyGuideArrow()
{
	polygon = NULL;
}

/**************************************
EnemyGuideArrow����������
***************************************/
void EnemyGuideArrow::Init()
{
	cntFrame = 0;
	active = true;
}

/**************************************
EnemyGuideArrow�I������
***************************************/
void EnemyGuideArrow::Uninit()
{
	active = false;
}

/**************************************
EnemyGuideArrow�X�V����
***************************************/
void EnemyGuideArrow::Update()
{
	if (!active)
		return;

	cntFrame++;

	if (cntFrame == ENEMYGUIDEARROW_LIFEFRAME)
		active = false;
}

/**************************************
EnemyGuideArrow�`�揈��
***************************************/
void EnemyGuideArrow::Draw()
{
	if (!active)
		return;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	transform.SetWorld();

	polygon->Draw();
}

/**************************************
EnemyGuideArrowEmitter�R���X�g���N�^
***************************************/
EnemyGuideArrowEmitter::EnemyGuideArrowEmitter()
{
	int containerSize = ENEMYGUIDEARROW_DURATION / ENEMYGUIDEARROW_INTERVAL;
	arrowContainer.resize(containerSize);
	for (auto& arrow : arrowContainer)
	{
		arrow = new EnemyGuideArrow();
	}

	active = false;
}

/**************************************
EnemyGuideArrowEmitter�f�X�g���N�^
***************************************/
EnemyGuideArrowEmitter::~EnemyGuideArrowEmitter()
{
	SAFE_DELETE_VECTOR(arrowContainer);
}

/**************************************
EnemyGuideArrowEmitter����������
***************************************/
void EnemyGuideArrowEmitter::Init(D3DXVECTOR3 start, D3DXVECTOR3 end)
{
	cntFrame = 0;
	cntArrow = 0;
	active = true;

	this->start = start;
	this->end = end;

	D3DXVECTOR3 diff = end - start;
	D3DXVec3Normalize(&diff, &diff);

	int dir = diff.x < 0 ? 1 : -1;
	float rotRadian = dir * acosf(D3DXVec3Dot(ENEMYGUIDEARROW_BASE_VECTOR, &diff));

	transform.IdentifyRotation();
	transform.Rotate(0.0f, 0.0f, D3DXToDegree(rotRadian));
}

/**************************************
EnemyGuideArrowEmitter�I������
***************************************/
void EnemyGuideArrowEmitter::Uninit()
{
	active = false;

	for (auto& arrow : arrowContainer)
	{
		arrow->Uninit();
	}

}

/**************************************
EnemyGuideArrowEmitter�X�V����
***************************************/
void EnemyGuideArrowEmitter::Update()
{
	if (!active)
		return;

	cntFrame++;

	float t = (float)cntFrame / ENEMYGUIDEARROW_DURATION;
	transform.pos = Easing::EaseValue(t, start, end, EaseType::Linear);

	if (cntFrame < ENEMYGUIDEARROW_DURATION && cntFrame % ENEMYGUIDEARROW_INTERVAL == 0)
	{
		arrowContainer[cntArrow]->transform = transform;
		arrowContainer[cntArrow]->Init();
		cntArrow++;
	}

	if (cntFrame >= ENEMYGUIDEARROW_DURATION)
	{
		bool isArrowAlive = false;
		for (auto& arrow : arrowContainer)
		{
			isArrowAlive |= arrow->active;
		}

		if (!isArrowAlive)
			Uninit();
	}

	for (auto& arrow : arrowContainer)
	{
		arrow->Update();
	}
}

/**************************************
EnemyGuideArrowEmitter�`�揈��
***************************************/
void EnemyGuideArrowEmitter::Draw()
{
	if (!active)
		return;

	for(auto& arrow : arrowContainer)
	{
		arrow->Draw();
	}
}