//=====================================
//
//ボスUIマネージャ処理[BossUIManager.cpp]
//Author:GP12A332 21 立花雄太
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
マクロ定義
***************************************/

/**************************************
コンストラクタ
***************************************/
BossUImanager::BossUImanager()
{
	warning = new WarningUI();
}

/**************************************
デストラクタ
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
更新処理
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
描画処理
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
ワーニングセット処理
***************************************/
void BossUImanager::SetWarning()
{

	//ワーニングSE
	Sound::GetInstance()->SetPlaySE(ALARM, true, (Sound::GetInstance()->changevol / 2.0f));

	warning->StartFade(true);
}

/**************************************
バレットガイドセット処理
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
