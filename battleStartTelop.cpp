//=============================================================================
//
// バトルスタートテロップ処理 [battleStartTelop->cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "telopBG.h"
#include "Framework/Easing.h"
#include "battleStartTelop.h"
#include "UIdrawer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SIZE_BATTLE_START_TELOP				(D3DXVECTOR3(SCREEN_WIDTH/4,50.0f,0.0f))
#define INIT_POSITION_BATTLE_START_TELOP	(D3DXVECTOR3(SCREEN_WIDTH*1.5,SCREEN_HEIGHT/10*8,0.0f))
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
BattleStartTelop::BattleStartTelop()
{
	battleStartTelop = new TelopObject();

	battleStartTelop->LoadTexture("data/TEXTURE/UI/Telop/battleStartTelop.png");
	battleStartTelop->MakeVertex();

	battleStartTelop->position = INIT_POSITION_BATTLE_START_TELOP;
	battleStartTelop->size = SIZE_BATTLE_START_TELOP;
	battleStartTelop->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	battleStartTelop->SetColorObject(SET_COLOR_NOT_COLORED);
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
BattleStartTelop::~BattleStartTelop()
{
	delete battleStartTelop;
	battleStartTelop = NULL;
}

//=============================================================================
// 更新処理
//=============================================================================
void BattleStartTelop::Update()
{	
	if (isBattleStartTelopActivated)
	{
		if (currentAnimation == WAIT_BG_OPEN && telopBG->GetTelopBGOpenActive() == false)
		{
			telopBG->AvctivateTelopBGOpen();
		}
		if (currentAnimation == WAIT_BG_CLOSE && telopBG->GetTelopBGCloseActive() == false)
		{
			telopBG->AvctivateTelopBGClose();
		}

		battleStartTelop->countFrame++;

		battleStartTelop->position.x = Easing::EaseValue(battleStartTelop->GetCountObject(AnimationDuration[currentAnimation]),
			EasingStartPositionX[currentAnimation],
			EasingEndPositionX[currentAnimation],
			AnimationType[currentAnimation]);

		if (battleStartTelop->countFrame == AnimationDuration[currentAnimation])
		{
			battleStartTelop->countFrame = 0;
			currentAnimation++;
		}
		if (currentAnimation == ANIMATION_MAX)
		{
			battleStartTelop->countFrame = 0;
			currentAnimation = 0;
			battleStartTelop->position = INIT_POSITION_BATTLE_START_TELOP;
			isBattleStartTelopActivated = false;
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void BattleStartTelop::Draw(void)
{
	battleStartTelop->Draw();
	battleStartTelop->SetVertex();
}
