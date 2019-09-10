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

/**************************************
グローバル変数
***************************************/
static GameSceneUIManager* instanceUImanager;

/**************************************
プロトタイプ宣言
***************************************/
int CheckInputTop(float x, float y);
int CheckInputMiddleLeft(float x, float y);
int CheckInputLowerLeft(float x, float y);
int CheckInputLowerRight(float x, float y);
int CheckInputMiddleRight(float x, float y);
int CheckInputCenter(float x, float y);

/**************************************
ゲームパッド以外での入力処理
***************************************/
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

/**************************************
ゲームパッドのスティックでの入力処理
***************************************/
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

/**************************************
一番上の☆にいるときのパッド入力処理
***************************************/
int CheckInputTop(float x, float y)
{
	const float BorderMiddleLeftX = -0.8f;		//MiddleLeftへ移動するスティックのX値
	const float BorderMiddleRightX = 0.8f;		//MiddleRightへ移動するスティックのX値
	const float BorderLowerY = -0.5f;			//Lowerへ移動するスティックのY値
	const float BorderLowerLeftX = -0.05f;		//LowerLeftへ移動するスティックのX値
	const float BorderLowerRightX = 0.05f;		//LowerRightへ移動するスティックのX値

	//MiddleLeftへの判定
	if (x < BorderMiddleLeftX)
		return MIDDLE_LEFT;

	//MiddleRightへの判定
	if (x > BorderMiddleRightX)
		return MIDDLE_RIGHT;

	//Lowerへの判定
	if (y < BorderLowerY)
	{
		//LowerLeftへの判定
		if (x < BorderLowerLeftX)
			return LOWER_LEFT;

		//LowerRightへの判定
		if (x > BorderLowerRightX)
			return LOWER_RIGHT;
	}

	return STAR_MAX;
}

/**************************************
左上の☆にいるときのパッド入力判定
***************************************/
int CheckInputMiddleLeft(float x, float y)
{
	const float BorderTopY = 0.8f;				//Topへ移動するスティックのY値
	const float BorderMiddleRightX = 0.9f;		//MiddleRightへ移動するスティックのX値
	const float BorderLowerRightX = 0.1f;		//LowerRightへ移動するスティックのX値
	const float BorderLowerRightY = 0.0f;		//LowerRightへ移動するスティックのY値
	const float BorderLowerLeftX = -0.1f;		//LowerLeftへ移動するスティックのX値

	//Topへの判定
	if (y > BorderTopY)
		return TOP;

	//MiddleRightへの判定
	if (x > BorderMiddleRightX)
		return MIDDLE_RIGHT;

	//LowerRightへの判定
	if (x > BorderLowerRightX && y < BorderLowerRightY)
		return LOWER_RIGHT;

	//LowerLeftへの判定
	if (y < BorderLowerLeftX)
		return LOWER_LEFT;

	return STAR_MAX;
}

/**************************************
左下の☆にいるときのパッド入力処理
***************************************/
int CheckInputLowerLeft(float x, float y)
{
	const float BorderMiddleLeftY = 0.7f;		//MiddleLeftとTopへ移動するスティックのY値
	const float BorderMiddleLeftX = -0.6f;		//MiddleLeftへ移動するスティックのX値
	const float BorderMiddleRightY = 0.3f;		//MiddleRightへ移動するスティックのY値
	const float BorderMiddleRightX = 0.3f;		//MiddleRightへ移動するスティックのX値
	const float BorderLowerRightX = 0.9f;		//LowerRightへ移動するスティックのX値

	//MiddleLeftとTopへの判定
	if (y > BorderMiddleLeftY)
	{
		//MiddleLeftへの判定
		if (x < BorderMiddleLeftX)
			return MIDDLE_LEFT;

		return TOP;
	}
	
	//MiddleRightへの判定
	if (y > BorderMiddleRightY && x > BorderMiddleRightX)
	{
		return MIDDLE_RIGHT;
	}

	//LowerRightへの判定
	if (x > BorderLowerRightX)
		return LOWER_RIGHT;

	return STAR_MAX;
}

/**************************************
右下の☆にいるときのパッド入力処理
***************************************/
int CheckInputLowerRight(float x, float y)
{
	const float BorderMiddleRightY = 0.7f;		//MiddleRightへ移動するスティックのY値
	const float BorderMiddleRightX = 0.6f;		//MiddleRightへ移動するスティックのX値
	const float BorderMiddleLeftX = -0.3f;		//MiddleLeftへ移動するスティックのX値
	const float BorderMiddleLeftY = 0.3f;		//MiddleLeftへ移動するスティックのY値
	const float BorderLowerLeftX = -0.9f;		//LowerLeftへ移動するスティックのX値

	//MiddleRightとTopへの判定
	if (y > BorderMiddleRightY)
	{
		//MiddleRightへの判定
		if (x > BorderMiddleRightX)
			return MIDDLE_RIGHT;

		return TOP;
	}

	//MiddleLeftへの判定
	if (y > BorderMiddleLeftY && x < BorderMiddleLeftX)
	{
		return MIDDLE_LEFT;
	}

	//LowerLeftへの判定
	if (x < BorderLowerLeftX)
		return LOWER_LEFT;

	return STAR_MAX;
}

/**************************************
右上の☆にいるときのパッド入力処理
***************************************/
int CheckInputMiddleRight(float x, float y)
{
	const float BorderTopY = 0.8f;				//Topへ移動するスティックのY値
	const float BorderMiddleLeftX = -0.9f;		//MiddleLeftへ移動するスティックのX値
	const float BorderLowerLeftX = -0.1f;		//LowerLeftへ移動するスティックのX値
	const float BorderLowerLeftY = 0.0f;		//LowerLeftへ移動するスティックのY値
	const float BorderLowerRightY = -0.1f;		//LowerRightへ移動するスティックのY値

	//Topへの判定
	if (y > BorderTopY)
		return TOP;

	//MiddleLeftへの判定
	if (x < BorderMiddleLeftX)
		return MIDDLE_LEFT;

	//LowerLeftへの判定
	if (x < BorderLowerLeftX && y < BorderLowerLeftY)
		return LOWER_LEFT;

	//LowerRightへの判定
	if (y < BorderLowerRightY)
		return LOWER_RIGHT;

	return STAR_MAX;
}

/**************************************
真ん中の☆にいるときのパッド入力処理
***************************************/
int CheckInputCenter(float x, float y)
{
	const float BorderTopY = 0.9f;				//Topへ移動するスティックのY値
	const float BorderLowerY = -0.5f;			//Lowerへ移動するスティックのY値
	const float BorderLowerRightX = 0.3f;		//LowerRightへ移動するスティックのX値
	const float BorderLowerLeftX = -0.3f;		//LowerLeftへ移動するスティックのX値
	const float BorderMiddleLeftX = -0.3f;		//MiddleLeftへ移動するスティックのX値
	const float BorderMiddleRightX = 0.3f;		//MiddleRightへ移動するスティックのX値

	//Topへの判定
	if (y > BorderTopY)
		return TOP;

	//Lowerへの判定
	if (y < BorderLowerY)
	{
		//LowerRightへの判定
		if (x > BorderLowerRightX)
			return LOWER_RIGHT;

		//LowerLeftへの判定
		if (x < BorderLowerLeftX)
			return LOWER_LEFT;
	}

	//MiddleLeftへの判定
	if (x < BorderMiddleLeftX)
	{
		return MIDDLE_LEFT;
	}

	//MiddleRightへの判定
	if (x > BorderMiddleRightX)
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

bool IsAnyButtonTriggerd()
{
	for (DWORD button = BUTTON_A; button < BUTTON_M; button = button << 1)
	{
		if (IsButtonTriggered(0, button))
			return true;
	}

	return false;
}
