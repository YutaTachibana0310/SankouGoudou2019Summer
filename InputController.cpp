//=============================================================================
//
// InputController���� [InputController.cpp]
// Author : �n糗Ǒ�
//
//=============================================================================
#include "input.h"
#include "starUI.h"
#include "sound.h"
#include "Game.h"
#include "masktex.h"



bool GetMoveInput(int m) {

	//�}�E�X�N���b�N�̌��o�����邩
	if (IsMouseLeftTriggered())
	{
		return IsStarSelected(m);
	}
	//�}�E�X�̓��͂��Ȃ��L�[�������ꂽ�ꍇ
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

bool GetBomberInput()
{
	if (IsMouseRightTriggered())
		return true;

	if (GetKeyboardTrigger(DIK_SPACE) || GetKeyboardTrigger(DIK_LSHIFT))
		return true;

	return false;
}

void InputSound() {



}

