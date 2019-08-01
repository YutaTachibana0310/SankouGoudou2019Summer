//=====================================
//
//エネミーガイドアローコントローラ処理[EnemyGuideArrowController.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "EnemyGuideArrowController.h"

#include "Framework\ResourceManager.h"
#include "LineTrailModel.h"
#include <algorithm>
#include "debugWindow.h"

using namespace std;

/**************************************
マクロ定義
***************************************/
#define ENEMYGUIDEARROW_SIZE		(D3DXVECTOR2(10.0f, 5.0f))
#define ENEMYGUIDEARROW_TEX_NAME	"data/TEXTURE/Enemy/GuideArrow.png"

/**************************************
コンストラクタ
***************************************/
EnemyGuideArrowController::EnemyGuideArrowController()
{
	//リソース作成
	ResourceManager::Instance()->MakePolygon("EnemyGuideArrow", ENEMYGUIDEARROW_TEX_NAME, ENEMYGUIDEARROW_SIZE);

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

	BeginDebugWindow("EnemyGuide");

	if (DebugButton("Set"))
	{
		int start = RandomRange(0, 5);
		int end = WrapAround(0, 5, start + RandomRange(1, 4));
		SetEmitter(LineTrailModel(start, end));
	}

	EndDebugWindow("EnemyGuide");

	for (auto& emitter : emitterContainer)
	{
		emitter->Update();
	}
}

/**************************************
描画処理
***************************************/
void EnemyGuideArrowController::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_LIGHTING, false);

	for (auto& emitter : emitterContainer)
	{
		emitter->Draw();
	}

	pDevice->SetRenderState(D3DRS_LIGHTING, true);
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
}