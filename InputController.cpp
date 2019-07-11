//=============================================================================
//
// InputController処理 [InputController.cpp]
// Author : 渡邉良則
//
//=============================================================================
#include "input.h"
#include "starUI.h"
#include "sound.h"
#include "Game.h"
#include "masktex.h"



bool IsEntered(int m) {

	//マウスクリックの検出があるか
	if (IsMouseLeftTriggered())
	{
		return IsStarSelected(m);
	}
	//マウスの入力がなくキーが押された場合
	else if (m == TOP) {
		return GetKeyboardTrigger(DIK_W);
	}
	else if (m == MIDDLE_LEFT) {
		return GetKeyboardTrigger(DIK_A);
	}
	else if (m == LOWER_LEFT) {
		return GetKeyboardTrigger(DIK_Z);
	}
	else if (m == LOWER_RIGHT) {
		return GetKeyboardTrigger(DIK_X);
	}
	else if (m == MIDDLE_RIGHT) {
		return GetKeyboardTrigger(DIK_D);
	}

	return false;
}

void InputSound() {



}

