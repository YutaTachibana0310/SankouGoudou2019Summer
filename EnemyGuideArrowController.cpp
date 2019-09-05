//=====================================
//
//エネミーガイドアローコントローラ処理[EnemyGuideArrowController.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "EnemyGuideArrowController.h"

#include "Framework\ResourceManager.h"
#include <algorithm>
#include "debugWindow.h"
#include "sound.h"

using namespace std;

/**************************************
マクロ定義
***************************************/
#define ENEMYGUIDEARROW_SIZE		(D3DXVECTOR2(7.5f, 3.0f))
#define ENEMYGUIDEARROW_TEX_NAME	"data/TEXTURE/Enemy/GuideArrow.png"
#define ENEMYGUIDEARROW_TEX_UV		(D3DXVECTOR2(1.0f, 1.0f))

/**************************************
コンストラクタ
***************************************/
EnemyGuideArrowController::EnemyGuideArrowController()
{
	//リソース作成
	ResourceManager::Instance()->MakePolygon("EnemyGuideArrow", ENEMYGUIDEARROW_TEX_NAME, ENEMYGUIDEARROW_SIZE, ENEMYGUIDEARROW_TEX_UV);

	//コンテナ作成
	for (auto& emitter : emitterContainer)
	{
		emitter = new EnemyGuideArrowEmitter();
	}
}

/**************************************
デストラクタ
***************************************/
EnemyGuideArrowController::~EnemyGuideArrowController()
{
	for (auto& emitter : emitterContainer)
	{
		SAFE_DELETE(emitter);
	}
}

/**************************************
更新処理
***************************************/
void EnemyGuideArrowController::Update()
{
	//予約確認
	for (auto& reserve : reserveList)
	{
		if (reserve.cntFrame == 0)
			SetEmitter(reserve.model);

		reserve.cntFrame--;
	}

	//エミッター更新
	for (auto& emitter : emitterContainer)
	{
		emitter->Update();
	}

	//終了した予約を削除
	remove_if(reserveList.begin(), reserveList.end(), [](auto reserve)
	{
		return reserve.cntFrame < 0;
	});
}

/**************************************
描画処理
***************************************/
void EnemyGuideArrowController::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_LIGHTING, false);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	pDevice->SetRenderState(D3DRS_ZENABLE, false);

	for (auto& emitter : emitterContainer)
	{
		emitter->Draw();
	}

	pDevice->SetRenderState(D3DRS_LIGHTING, true);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState(D3DRS_ZENABLE, true);
}

/**************************************
エミッターセット処理
***************************************/
void EnemyGuideArrowController::SetEmitter(LineTrailModel model)
{
	auto itr = find_if(emitterContainer.begin(), emitterContainer.end(), [](EnemyGuideArrowEmitter* emitter)
	{
		return !emitter->active;
	});

	if (itr == emitterContainer.end())
		return;

	D3DXVECTOR3 start, end;
	model.GetEdgePos(&start, &end);
	(*itr)->Init(start, end);
	//エミッターセットSE
	Sound::GetInstance()->SetPlaySE(ENEMYNOTICE, true, (Sound::GetInstance()->changevol / 20.0f));
}

/**************************************
エミッター予約処理
***************************************/
void EnemyGuideArrowController::Reserve(int delay, LineTrailModel model)
{
	reserveList.push_back(EnemyGuideReserve(delay, model));
}