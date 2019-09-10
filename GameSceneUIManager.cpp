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
#include "starButtonUI.h"
#include "comboUI.h"
#include "trailUI.h"
#include "cursorUI.h"
#include "battleStartTelop.h"
#include "stageClearTelop.h"
#include "telopBG.h"
#include "bomberStockUI.h"
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
	starButton = new StarButton();
	cursor = new Cursor();
	combo = new Combo();
	guage = new Guage();
	score = new Score();
	trail = new Trail();
	battleStartTelop = new BattleStartTelop();
	stageClearTelop = new StageClearTelop();
	telopBG = new TelopBG();
	bomberStock = new BomberStock();
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
GameSceneUIManager::~GameSceneUIManager()
{
	SAFE_DELETE(combo);
	SAFE_DELETE(cursor);
	SAFE_DELETE(guage);
	SAFE_DELETE(score);
	SAFE_DELETE(starButton);
	SAFE_DELETE(trail);
	SAFE_DELETE(battleStartTelop);
	SAFE_DELETE(stageClearTelop);
	SAFE_DELETE(telopBG);
	SAFE_DELETE(bomberStock);
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
	score->Update();
	starButton->Update(hWnd);
	trail->Update();
	battleStartTelop->Update();
	stageClearTelop->Update();
	telopBG->Update();
	bomberStock->Update();

#if 0
	// デバッグ用コマンド
	if (GetKeyboardTrigger(DIK_1))
	{
		AddCombo(1);
	}
	if (GetKeyboardTrigger(DIK_2))
	{
		AddScore(1);
	}
	if (GetKeyboardTrigger(DIK_3))
	{
		SetStageClearTelop();
	}
	if (GetKeyboardTrigger(DIK_4))
	{
		SetBattleStartTelop();
	}
	if (GetKeyboardTrigger(DIK_5))
	{
		SetHPGuage(0.5f);
	}
	if (GetKeyboardTrigger(DIK_6))
	{
		SetBomberStock(3);
	}

	if (GetKeyboardTrigger(DIK_7))
	{
		SetBomberStock(4);
	}
#endif

	guage->Update();

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
	score->Draw();
	starButton->Draw();
	trail->Draw();
	bomberStock->Draw();
	telopBG->Draw();
	battleStartTelop->Draw();
	stageClearTelop->Draw();

	cursor->Draw();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
}


//=============================================================================
// カーソルの色更新判定処理
//=============================================================================
bool GameSceneUIManager::IsStarCursorOvered()
{
	std::vector<D3DXVECTOR3> starButtonPos;
	GetStarPosition(starButtonPos);

	// どのスターとも当たってなかったらfalse,それ以外はtrue
	if (cursor->IsCursorOvered(starButtonPos[0], COLLIDERSIZE_STAR))
		return true;

	if (cursor->IsCursorOvered(starButtonPos[1], COLLIDERSIZE_STAR))
		return true;

	if (cursor->IsCursorOvered(starButtonPos[2], COLLIDERSIZE_STAR))
		return true;

	if (cursor->IsCursorOvered(starButtonPos[3], COLLIDERSIZE_STAR))
		return true;

	if (cursor->IsCursorOvered(starButtonPos[4], COLLIDERSIZE_STAR))
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
	starButton->GetStarButtonPosition(out);
}

//=============================================================================
// スターボタン入力確認
//=============================================================================
int GameSceneUIManager::IsStarSelected()
{
	std::vector<D3DXVECTOR3> starButtonPos;
	GetStarPosition(starButtonPos);

	for (int i = 0; i < 5; i++)
	{
		if (cursor->IsCursorOvered(starButtonPos[i], COLLIDERSIZE_STAR))
			return i;
	}

	return 5;
}

//=============================================================================
// HPゲージセット処理(引数で与えられた割合(0.0f～1.0f)にゲージをセットする)
//=============================================================================
void GameSceneUIManager::SetHPGuage(float percentage)
{
	guage->trueGuagePercentage = percentage;
}

//=============================================================================
// ボムストックセット処理(引数で与えられた数分ボンバーストックをセットする)
//=============================================================================
void GameSceneUIManager::SetBomberStock(int stockedBomNum, bool isCharging)
{
	//*注意：今は仮でmax3にしてます。
	if (stockedBomNum > MAX_STOCKED_BOM_NUM)
	{
		//メモリ破壊対策
		return;
	}

	bomberStock->stockedBomNum = stockedBomNum;
	bomberStock->isCharging = isCharging;
}
