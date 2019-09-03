//=============================================================================
//
// GameシーンUI管理処理 [GameSceneUIManagerManager.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "guageUI.h"
#include "scoreUI.h"
#include "starUI.h"
#include "comboUI.h"
#include "lineUI.h"
#include "trailUI.h"
#include "cursorUI.h"
#include "battleStartTelop.h"
#include "stageClearTelop.h"
#include "telopBG.h"
#include "GameSceneUIManager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
//#define GAME_SCENE_UI_MAX (10)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
//GameSceneUIManager *gameSceneUI[GAME_SCENE_UI_MAX];

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
GameSceneUIManager::GameSceneUIManager()
{
	line = new Line();
	star = new Star();
	cursor = new Cursor();
	combo = new Combo();
	guage = new Guage();
	score = new Score();
	trail = new Trail();
	battleStartTelop = new BattleStartTelop();
	stageClearTelop = new StageClearTelop();
	telopBG = new TelopBG();
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
GameSceneUIManager::~GameSceneUIManager()
{
	delete combo;
	combo = NULL;

	delete cursor;
	cursor = NULL;

	delete guage;
	guage = NULL;

	delete line;
	line = NULL;

	delete score;
	score = NULL;

	delete star;
	star = NULL;

	delete trail;
	trail = NULL;

	delete battleStartTelop;
	battleStartTelop = NULL;

	delete stageClearTelop;
	stageClearTelop = NULL;

	delete telopBG;
	telopBG = NULL;
}

//=============================================================================
// 初期化処理
//=============================================================================
void GameSceneUIManager::Init()
{
}

//=============================================================================
// 終了処理
//=============================================================================
void GameSceneUIManager::Uninit()
{

}


//=============================================================================
// 更新処理
//=============================================================================
void GameSceneUIManager::Update(HWND hWnd)
{
	combo->Update();
	cursor->Update(hWnd);
	guage->Update();
	line->Update();
	score->Update();
	star->Update(hWnd);
	trail->Update();
	battleStartTelop->Update();
	stageClearTelop->Update();
	telopBG->Update();

#ifdef _DEBUG
	// デバッグ用コマンド
	if (GetKeyboardTrigger(DIK_1))
	{
	}
	if (GetKeyboardTrigger(DIK_2))
	{
	}
	if (GetKeyboardTrigger(DIK_3))
	{
	}
	if (GetKeyboardTrigger(DIK_4))
	{
	}
	if (GetKeyboardTrigger(DIK_5))
	{
	}
	if (GetKeyboardTrigger(DIK_6))
	{
	}
	if (GetKeyboardTrigger(DIK_7))
	{
	}
#endif

	UpdateCursorColor();
}

//=============================================================================
// 描画処理
//=============================================================================
void GameSceneUIManager::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	combo->Draw();
	guage->Draw();
	line->Draw();
	score->Draw();
	star->Draw();
	trail->Draw();
	battleStartTelop->Draw();
	stageClearTelop->Draw();
	telopBG->Draw();

	cursor->Draw();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
}


//=============================================================================
// カーソルの色更新判定処理
//=============================================================================
bool GameSceneUIManager::IsStarCursorOvered()
{
	std::vector<D3DXVECTOR3> starPos;
	GetStarPosition(starPos);

	// どのスターとも当たってなかったらfalse,それ以外はtrue
	if (cursor->IsCursorOvered(starPos[0], COLLIDERSIZE_STAR))
		return true;

	if (cursor->IsCursorOvered(starPos[1], COLLIDERSIZE_STAR))
		return true;

	if (cursor->IsCursorOvered(starPos[2], COLLIDERSIZE_STAR))
		return true;

	if (cursor->IsCursorOvered(starPos[3], COLLIDERSIZE_STAR))
		return true;

	if (cursor->IsCursorOvered(starPos[4], COLLIDERSIZE_STAR))
		return true;

	return false;
}

//=============================================================================
// カーソルの色更新処理
//=============================================================================
void GameSceneUIManager::UpdateCursorColor()
{
	if (IsStarCursorOvered())
	{
		// 選択されているなら
		cursor->PaintCursorRed();
	}
	else
	{	// 元に戻す
		cursor->PaintCursorYellow();
	}
}


//=============================================================================
// コンボの加算（引数で受け取った値をコンボに加算する）
//=============================================================================
void  GameSceneUIManager::AddCombo(int value)
{
	combo->combo += value;

	if (value > 0)
	{
		combo->volumeUpEffectUsed = true;
	}
}
//=============================================================================
// コンボのセット
//=============================================================================
void  GameSceneUIManager::SetCombo(int num)
{
	num = combo->combo;
}

//=============================================================================
// コンボのリセット
//=============================================================================
void GameSceneUIManager::ReSetCombo(void)
{
	combo->combo = 0;
}

//=============================================================================
// スコアの加算（引数で受け取った値をスコアに加算する）
//=============================================================================
void  GameSceneUIManager::AddScore(int value)
{
	score->score += value;

	// スコアが加算されたら行う処理
	if (value > 0)
	{
		// エフェクト有効化
		score->volumeUpEffectUsed = true;
	}
}

//=============================================================================
// スコアのセット
//=============================================================================
void  GameSceneUIManager::SetScore(int num)
{
	num = score->score;
}

//=============================================================================
// HPの加算（引数で受け取った値をHOに加算する）
//=============================================================================
void  GameSceneUIManager::AddHp(float value)
{
	guage->trueGuagePercentage += (value /= guage->maxHp);
}

//=============================================================================
// ステージクリアテロップセット処理
//=============================================================================
void  GameSceneUIManager::SetStageClearTelop(void)
{
	stageClearTelop->isStageClearTelopActivated = true;
}

//=============================================================================
// バトルスタートテロップセット処理
//=============================================================================
void  GameSceneUIManager::SetBattleStartTelop(void)
{
	battleStartTelop->isBattleStartTelopActivated = true;
}

//=============================================================================
// スター座標ゲット処理
//=============================================================================
void  GameSceneUIManager::GetStarPosition(std::vector<D3DXVECTOR3>& out)
{
	star->GetStarPosition(out);
}

//=============================================================================
// スター座標セット処理
//=============================================================================
void  GameSceneUIManager::SetStarPosition(D3DXVECTOR3* pos)
{
	//pos = star->GetStarPosition();
}
