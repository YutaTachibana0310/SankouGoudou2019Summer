//=============================================================================
//
// InputController処理 [InputController.cpp]
// Author : 渡邉良則
//
//=============================================================================
#include "InputController.h"
#include "input.h"
#include "sound.h"
#include "GameSceneUIManager.h"
#include "starButtonUI.h"

static GameSceneUIManager* instanceUImanager;

int CheckInputTop();
int CheckInputMiddleLeft();
int CheckInputLowerLeft();
int CheckInputLowerRight();
int CheckInputMiddleRight();

int GetMoveInput() {

	//マウスクリックの検出があるか
	if (IsMouseLeftTriggered())
	{
		int starButtonID = instanceUImanager->IsStarSelected();

		if (starButtonID < STAR_MAX)
			return	starButtonID;
	}

	if (GetKeyboardTrigger(DIK_W))
		return TOP;

	if (GetKeyboardTrigger(DIK_A))
		return MIDDLE_LEFT;

	if (GetKeyboardTrigger(DIK_Z))
		return LOWER_LEFT;

	if (GetKeyboardTrigger(DIK_X))
		return LOWER_RIGHT;

	if (GetKeyboardTrigger(DIK_D))
		return MIDDLE_RIGHT;

	return STAR_MAX;
}

int GetStickInput(int currentStar)
{
	if (currentStar == TOP)
		return CheckInputTop();

	if (currentStar == MIDDLE_LEFT)
		return CheckInputMiddleLeft();

	if (currentStar == LOWER_LEFT)
		return CheckInputLowerLeft();

	if (currentStar == LOWER_RIGHT)
		return CheckInputLowerRight();

	if (currentStar == MIDDLE_RIGHT)
		return CheckInputMiddleRight();
	
	return STAR_MAX;
}

int CheckInputTop()
{
	if (IsButtonTriggered(0, BUTTON_LEFT))
	{
		if (IsButtonTriggered(0, BUTTON_DOWN))
			return LOWER_LEFT;

		return MIDDLE_LEFT;
	}

	if (IsButtonTriggered(0, BUTTON_RIGHT))
	{
		if (IsButtonTriggered(0, BUTTON_DOWN))
			return LOWER_RIGHT;

		return MIDDLE_RIGHT;
	}

	return STAR_MAX;
}

int CheckInputMiddleLeft()
{
	if (IsButtonTriggered(0, BUTTON_RIGHT))
	{
		if (IsButtonTriggered(0, BUTTON_DOWN))
			return LOWER_RIGHT;

		return MIDDLE_RIGHT;
	}

	if (IsButtonTriggered(0, BUTTON_UP))
		return TOP;

	if (IsButtonTriggered(0, BUTTON_DOWN))
		return LOWER_LEFT;

	return STAR_MAX;
}

int CheckInputLowerLeft()
{
	if (IsButtonTriggered(0, BUTTON_RIGHT))
	{
		if (IsButtonTriggered(0, BUTTON_UP))
			return MIDDLE_RIGHT;

		return LOWER_RIGHT;
	}

	if (IsButtonTriggered(0, BUTTON_UP))
	{
		if (IsButtonTriggered(0, BUTTON_LEFT))
			return MIDDLE_LEFT;

		return TOP;
	}

	return STAR_MAX;
}

int CheckInputLowerRight()
{
	if (IsButtonTriggered(0, BUTTON_LEFT))
	{
		if (IsButtonTriggered(0, BUTTON_UP))
			return MIDDLE_LEFT;

		return LOWER_LEFT;
	}

	if (IsButtonTriggered(0, BUTTON_UP))
	{
		if (IsButtonTriggered(0, BUTTON_RIGHT))
			return MIDDLE_RIGHT;

		return TOP;
	}

	return STAR_MAX;
}

int CheckInputMiddleRight()
{
	if (IsButtonTriggered(0, BUTTON_LEFT))
	{
		if (IsButtonTriggered(0, BUTTON_DOWN))
			return LOWER_LEFT;

		return MIDDLE_LEFT;
	}

	if (IsButtonTriggered(0, BUTTON_UP))
		return TOP;

	if (IsButtonTriggered(0, BUTTON_DOWN))
		return LOWER_RIGHT;

	return STAR_MAX;
}

bool GetBomberInput()
{
	if (IsMouseRightTriggered())
		return true;

	if (GetKeyboardTrigger(DIK_SPACE) || GetKeyboardTrigger(DIK_LSHIFT))
		return true;

	return false;
}


void SetInstanceUIManager(GameSceneUIManager * instance)
{
	instanceUImanager = instance;
}

bool IsAnyKeyTriggered()
{
	for (int i = DIK_ESCAPE; i < DIK_F1; i++)
	{
		if (GetKeyboardTrigger(i))
			return true;
	}

	return false;
}

