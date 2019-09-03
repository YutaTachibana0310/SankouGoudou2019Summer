//=============================================================================
//
// ResultシーンUI管理処理 [ResultSceneUIManager.cpp]
// Author :
//
//=============================================================================
#include "main.h"
#include "rank.h"
#include "resultBGUI.h"

#include "ResultSceneUIManager.h"

//=============================================================================
// 初期化処理
//=============================================================================
void InitResultSceneUI(void) {
	InitResultBG();
	InitRank();
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitResultSceneUI(void) {
	UninitResultBG();
	UninitRank();
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateResultSceneUI(HWND hwnd) {
	UpdateResultBG();
	UpdateRank();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawResultSceneUI(void) {
	DrawResultBG();
	DrawRank();
}