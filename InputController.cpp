//=============================================================================
//
// InputControllerâÊñ èàóù [InputController.cpp]
// Author : ìnÁ≥ó«ë•
//
//=============================================================================
#include "input.h"
#include "star.h"

bool IsEntered(int m, HWND hWnd) {

	if (IsMouseLeftTriggered())
	{
		return IsSelected(m, hWnd);
	}
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

}