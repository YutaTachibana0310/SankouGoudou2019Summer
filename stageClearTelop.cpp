//=============================================================================
//
// ステージクリアテロップ処理 [stageClearTelop->cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "telopBG.h"
#include "Framework/Easing.h"
#include "stageClearTelop.h"
#include "UIdrawer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SIZE_STAGE_CLEAR_TELOP				(D3DXVECTOR3(SCREEN_WIDTH/4,50.0f,0.0f))
#define INIT_POSITION_STAGE_CLEAR_TELOP	(D3DXVECTOR3(SCREEN_WIDTH*1.5,SCREEN_HEIGHT/10*8,0.0f))
#define ANIMATION_MAX (5)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static int currentAnimation = 0;

static const float EasingStartPositionX[ANIMATION_MAX] = {
	SCREEN_WIDTH*1.5,
	SCREEN_WIDTH*1.5,
	SCREEN_CENTER_X,
	SCREEN_CENTER_X,
	-SCREEN_WIDTH * 1.5
};

static const float EasingEndPositionX[ANIMATION_MAX] = {
	SCREEN_WIDTH*1.5,
	SCREEN_CENTER_X,
	SCREEN_CENTER_X,
	-SCREEN_WIDTH * 1.5,
	-SCREEN_WIDTH * 1.5
};

static const EaseType AnimationType[ANIMATION_MAX] = {
	InOutCubic,
	InOutCubic,
	InOutCubic,
	InOutCubic,
	InOutCubic
};

static const float AnimationDuration[ANIMATION_MAX] = {
	10,
	120,
	100,
	120,
	10
};

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
StageClearTelop::StageClearTelop()
{
	stageClearTelop = new TelopObject();

	stageClearTelop->LoadTexture("data/TEXTURE/UI/Telop/stageClearTelop.png");
	stageClearTelop->MakeVertex();

	stageClearTelop->position = INIT_POSITION_STAGE_CLEAR_TELOP;
	stageClearTelop->size = SIZE_STAGE_CLEAR_TELOP;
	stageClearTelop->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	stageClearTelop->SetColorObject(SET_COLOR_NOT_COLORED);
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
StageClearTelop::~StageClearTelop()
{
	delete stageClearTelop;
	stageClearTelop = NULL;
}

//=============================================================================
// 更新処理
//=============================================================================
void StageClearTelop::Update()
{
	if (isStageClearTelopActivated)
	{
		if (currentAnimation == WAIT_BG_OPEN && telopBG->GetTelopBGOpenActive() == false)
		{
			telopBG->AvctivateTelopBGOpen();
		}
		if (currentAnimation == WAIT_BG_CLOSE && telopBG->GetTelopBGCloseActive() == false)
		{
			telopBG->AvctivateTelopBGClose();
		}

		stageClearTelop->countFrame++;

		stageClearTelop->position.x = Easing::EaseValue(stageClearTelop->GetCountObject(AnimationDuration[currentAnimation]),
			EasingStartPositionX[currentAnimation],
			EasingEndPositionX[currentAnimation],
			AnimationType[currentAnimation]);

		if (stageClearTelop->countFrame == AnimationDuration[currentAnimation])
		{
			stageClearTelop->countFrame = 0;
			currentAnimation++;
		}
		if (currentAnimation == ANIMATION_MAX)
		{
			stageClearTelop->countFrame = 0;
			currentAnimation = 0;
			stageClearTelop->position = INIT_POSITION_STAGE_CLEAR_TELOP;
			isStageClearTelopActivated = false;
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void StageClearTelop::Draw(void)
{
	stageClearTelop->Draw();
	stageClearTelop->SetVertex();
}
