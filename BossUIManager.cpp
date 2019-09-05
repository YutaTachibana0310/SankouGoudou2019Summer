//=====================================
//
//�{�XUI�}�l�[�W������[BossUIManager.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "BossUIManager.h"
#include "WarningUI.h"
#include "BossBulletGuide.h"
#include "LineTrailModel.h"
#include "camera.h"
#include <algorithm>
#include "sound.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
BossUImanager::BossUImanager()
{
	warning = new WarningUI();
}

/**************************************
�f�X�g���N�^
***************************************/
BossUImanager::~BossUImanager()
{
	SAFE_DELETE(warning);

	for (auto&& guide : bulletGuide)
	{
		SAFE_DELETE(guide);
	}
}

/**************************************
�X�V����
***************************************/
void BossUImanager::Update()
{
	warning->Update();

	for (auto&& guide : bulletGuide)
	{
		guide->Update();
	}
}

/**************************************
�`�揈��
***************************************/
void BossUImanager::Draw()
{
	warning->Draw();

	for (auto&& guide : bulletGuide)
	{
		if(guide->IsActive())	
			guide->Draw();
	}
}

/**************************************
���[�j���O�Z�b�g����
***************************************/
void BossUImanager::SetWarning()
{

	//���[�j���OSE
	Sound::GetInstance()->SetPlaySE(ALARM, true, (Sound::GetInstance()->changevol / 2.0f));

	warning->StartFade(true);
}

/**************************************
�o���b�g�K�C�h�Z�b�g����
***************************************/
void BossUImanager::SetBulletGuide(LineTrailModel & model)
{
	D3DXVECTOR3 right, left;
	model.GetEdgePos(&right, &left);

	D3DXVECTOR3 edgeR, edgeL;
	Camera::Instance()->Projection(edgeR, right);
	Camera::Instance()->Projection(edgeL, left);

	const int SetNum = 5;
	D3DXVECTOR3 offset = (edgeR - edgeL) / (SetNum + 1);
	edgeL += offset;

	for (int i = 0; i < SetNum; i++)
	{
		auto itr = find_if(bulletGuide.begin(), bulletGuide.end(), [](auto&& guide)
		{
			return !guide->IsActive();
		});

		if (itr == bulletGuide.end())
		{
			BossBulletGuide* ptr = new BossBulletGuide();
			ptr->Set(edgeL);
			bulletGuide.push_back(ptr);
		}
		else
		{
			(*itr)->Set(edgeL);
		}
		edgeL += offset;
	}
}
