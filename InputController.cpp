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

int CheckInputTop(float x, float y);
int CheckInputMiddleLeft(float x, float y);
int CheckInputLowerLeft(float x, float y);
int CheckInputLowerRight(float x, float y);
int CheckInputMiddleRight(float x, float y);
int CheckInputCenter(float x, float y);

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
	float x = GetAxisX(0);
	float y = GetAxisY(0);

	if (currentStar == TOP)
		return CheckInputTop(x, y);

	if (currentStar == MIDDLE_LEFT)
		return CheckInputMiddleLeft(x, y);

	if (currentStar == LOWER_LEFT)
		return CheckInputLowerLeft(x, y);

	if (currentStar == LOWER_RIGHT)
		return CheckInputLowerRight(x, y);

	if (currentStar == MIDDLE_RIGHT)
		return CheckInputMiddleRight(x, y);

	if (currentStar == STAR_MAX)
		return CheckInputCenter(x, y);

	return STAR_MAX;
}

int CheckInputTop(float x, float y)
{
	if (x < -0.8f)
		return MIDDLE_LEFT;

	if (x > 0.8f)
		return MIDDLE_RIGHT;

	if (y < -0.5f)
	{
		if (x < -0.05f)
			return LOWER_LEFT;

		if (x > 0.05f)
			return LOWER_RIGHT;
	}

	return STAR_MAX;
}

int CheckInputMiddleLeft(float x, float y)
{
	if (y > 0.8f)
		return TOP;

	if (x > 0.9f)
		return MIDDLE_RIGHT;

	if (x > 0.1f && y < 0.0f)
		return LOWER_RIGHT;

	if (y < -0.1f)
		return LOWER_LEFT;

	return STAR_MAX;
}

int CheckInputLowerLeft(float x, float y)
{
	if (y > 0.7f)
	{
		if (x < -0.6f)
			return MIDDLE_LEFT;

		return TOP;
	}

	if (y > 0.3f && x > 0.3f)
	{
		return MIDDLE_RIGHT;
	}

	if (x > 0.9f)
		return LOWER_RIGHT;

	return STAR_MAX;
}

int CheckInputLowerRight(float x, float y)
{
	if (y > 0.7f)
	{
		if (x < -0.6f)
			return MIDDLE_RIGHT;

		return TOP;
	}

	if (y > 0.3f && x > 0.3f)
	{
		return MIDDLE_LEFT;
	}

	if (x < -0.9f)
		return LOWER_LEFT;

	return STAR_MAX;
}

int CheckInputMiddleRight(float x, float y)
{
	if (y > 0.8f)
		return TOP;

	if (x < -0.9f)
		return MIDDLE_LEFT;

	if (x < -0.1f && y < 0.0f)
		return LOWER_LEFT;

	if (y < -0.1f)
		return LOWER_RIGHT;

	return STAR_MAX;
}

int CheckInputCenter(float x, float y)
{
	if (y > 0.9f)
		return TOP;

	if (y < -0.5f)
	{
		if (x > 0.3f)
			return LOWER_RIGHT;

		if (x < -0.3f)
			return LOWER_LEFT;
	}

	if (x < -0.3f)
	{
		return MIDDLE_LEFT;
	}

	if (x > 0.3f)
	{
		return MIDDLE_RIGHT;
	}

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

