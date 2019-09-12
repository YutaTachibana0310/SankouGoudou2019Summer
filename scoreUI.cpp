//=============================================================================
//
// スコア処理 [score.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "UIdrawer.h"
#include "Viewer3D.h"
#include "input.h"
#include "scoreUI.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SPEED_VOLUMEUP_NUMBER_SCORE (0.2f)
#define SIZE_NUMBER_SCORE	(D3DXVECTOR3(120.0f,200.0f,0.0f))
#define SIZE_BG_SCORE		(D3DXVECTOR3(1024.0f,256.0f,0.0f))

//座標設定(3D)
#define POSITION_NUMBER_SCORE	(D3DXVECTOR3(240.0f,300.0f,0.0f))
#define POSITION_BG_SCORE		(D3DXVECTOR3(1024.0f,256.0f,0.0f))

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
Score::Score()
{
	//カウンター
	counter = new CounterObject();
	counter->LoadTexture("data/TEXTURE/UI/Score/number_L.png");
	counter->MakeVertex();
	counter->position = POSITION_NUMBER_SCORE/2;
	counter->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	counter->size = SIZE_NUMBER_SCORE/2;
	counter->SetColorObject(SET_COLOR_NOT_COLORED);

	//背景
	bg = new CounterObject();
	bg->LoadTexture("data/TEXTURE/UI/Score/scoreBG.png");
	bg->MakeVertex();
	bg->position = POSITION_BG_SCORE/2;
	bg->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bg->size = SIZE_BG_SCORE/2;
	bg->SetColorObject(SET_COLOR_NOT_COLORED);

	//ビュアー
	viewer = new Viewer3D((DWORD)SIZE_BG_SCORE.x, (DWORD)SIZE_BG_SCORE.y, D3DXVECTOR2(35.0f, 10.0f));
	viewer->SetPosition(D3DXVECTOR3((float)-SCREEN_WIDTH/18.0f,(float)SCREEN_HEIGHT / 16.0f, 0.0f));
	viewer->SetRotation(0.0f, -30.0f, 0.0f);

	// 最大値設定
	for (int nCntPlace = 0; nCntPlace < PLACE_MAX; nCntPlace++)
	{
		score_max += (BASE_NUMBER - 1)* (int)powf(BASE_NUMBER, (float)nCntPlace);
	}

	score = 0;
	radian = 0;
	volumeUpEffectUsed = false;
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
Score::~Score()
{
	SAFE_DELETE(counter);
	SAFE_DELETE(bg);
	SAFE_DELETE(viewer);
}
//#include "debugWindow.h"
//=============================================================================
// 更新処理
//=============================================================================
void Score::Update(void)
{
	//BeginDebugWindow("score");
	//static float angle = 30.0f;
	//DebugSliderFloat("angle", &angle, -90.0f, 0.0f);
	//viewer->SetRotation(0.0f, angle, 0.0f);
	//EndDebugWindow("");
	VolumeUpEffect();

	// 桁あふれ防止
	if (score < 0)
	{
		score = 0;
	}
	if (score >= score_max)
	{
		score = score_max;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void Score::Draw(void)
{
	viewer->Begin2D();

	bg->Draw();
	bg->SetVertex();

	for (int nCntPlace = 0; nCntPlace < PLACE_MAX; nCntPlace++)
	{
		int scoreber;

		scoreber = score % (int)(powf(BASE_NUMBER, (float)(PLACE_MAX - nCntPlace))) / (int)(powf(BASE_NUMBER, (float)(PLACE_MAX - nCntPlace - 1)));

		counter->Draw();
		counter->SetVertex(nCntPlace, INTERVAL_NUMBER);
		counter->SetTexture(scoreber, INTERVAL_NUMBER_TEXTURE);
	}

	viewer->End2D();
	viewer->Draw3D();
}

//=============================================================================
// 数字ボリュームアップエフェクト処理
//=============================================================================
void Score::VolumeUpEffect(void)
{
	if (volumeUpEffectUsed == true)
	{
		counter->size.y = SIZE_NUMBER_SCORE.y/2 + VOLUME_ZOOM * sinf(radian);

		if (radian >= D3DX_PI)
		{
			radian = 0.0f;
			volumeUpEffectUsed = false;
		}

		radian += SPEED_VOLUMEUP_NUMBER_SCORE;
	}
}
