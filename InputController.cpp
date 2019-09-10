//=============================================================================
//
// InputController���� [InputController.cpp]
// Author : �n糗Ǒ�
//
//=============================================================================
#include "InputController.h"
#include "input.h"
#include "sound.h"
#include "GameSceneUIManager.h"
#include "starButtonUI.h"

/**************************************
�O���[�o���ϐ�
***************************************/
static GameSceneUIManager* instanceUImanager;

/**************************************
�v���g�^�C�v�錾
***************************************/
int CheckInputTop(float x, float y);
int CheckInputMiddleLeft(float x, float y);
int CheckInputLowerLeft(float x, float y);
int CheckInputLowerRight(float x, float y);
int CheckInputMiddleRight(float x, float y);
int CheckInputCenter(float x, float y);

/**************************************
�Q�[���p�b�h�ȊO�ł̓��͏���
***************************************/
int GetMoveInput() {

	//�}�E�X�N���b�N�̌��o�����邩
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
�Q�[���p�b�h�̃X�e�B�b�N�ł̓��͏���
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
��ԏ�́��ɂ���Ƃ��̃p�b�h���͏���
***************************************/
int CheckInputTop(float x, float y)
{
	const float BorderMiddleLeftX = -0.8f;		//MiddleLeft�ֈړ�����X�e�B�b�N��X�l
	const float BorderMiddleRightX = 0.8f;		//MiddleRight�ֈړ�����X�e�B�b�N��X�l
	const float BorderLowerY = -0.5f;			//Lower�ֈړ�����X�e�B�b�N��Y�l
	const float BorderLowerLeftX = -0.05f;		//LowerLeft�ֈړ�����X�e�B�b�N��X�l
	const float BorderLowerRightX = 0.05f;		//LowerRight�ֈړ�����X�e�B�b�N��X�l

	//MiddleLeft�ւ̔���
	if (x < BorderMiddleLeftX)
		return MIDDLE_LEFT;

	//MiddleRight�ւ̔���
	if (x > BorderMiddleRightX)
		return MIDDLE_RIGHT;

	//Lower�ւ̔���
	if (y < BorderLowerY)
	{
		//LowerLeft�ւ̔���
		if (x < BorderLowerLeftX)
			return LOWER_LEFT;

		//LowerRight�ւ̔���
		if (x > BorderLowerRightX)
			return LOWER_RIGHT;
	}

	return STAR_MAX;
}

/**************************************
����́��ɂ���Ƃ��̃p�b�h���͔���
***************************************/
int CheckInputMiddleLeft(float x, float y)
{
	const float BorderTopY = 0.8f;				//Top�ֈړ�����X�e�B�b�N��Y�l
	const float BorderMiddleRightX = 0.9f;		//MiddleRight�ֈړ�����X�e�B�b�N��X�l
	const float BorderLowerRightX = 0.1f;		//LowerRight�ֈړ�����X�e�B�b�N��X�l
	const float BorderLowerRightY = 0.0f;		//LowerRight�ֈړ�����X�e�B�b�N��Y�l
	const float BorderLowerLeftX = -0.1f;		//LowerLeft�ֈړ�����X�e�B�b�N��X�l

	//Top�ւ̔���
	if (y > BorderTopY)
		return TOP;

	//MiddleRight�ւ̔���
	if (x > BorderMiddleRightX)
		return MIDDLE_RIGHT;

	//LowerRight�ւ̔���
	if (x > BorderLowerRightX && y < BorderLowerRightY)
		return LOWER_RIGHT;

	//LowerLeft�ւ̔���
	if (y < BorderLowerLeftX)
		return LOWER_LEFT;

	return STAR_MAX;
}

/**************************************
�����́��ɂ���Ƃ��̃p�b�h���͏���
***************************************/
int CheckInputLowerLeft(float x, float y)
{
	const float BorderMiddleLeftY = 0.7f;		//MiddleLeft��Top�ֈړ�����X�e�B�b�N��Y�l
	const float BorderMiddleLeftX = -0.6f;		//MiddleLeft�ֈړ�����X�e�B�b�N��X�l
	const float BorderMiddleRightY = 0.3f;		//MiddleRight�ֈړ�����X�e�B�b�N��Y�l
	const float BorderMiddleRightX = 0.3f;		//MiddleRight�ֈړ�����X�e�B�b�N��X�l
	const float BorderLowerRightX = 0.9f;		//LowerRight�ֈړ�����X�e�B�b�N��X�l

	//MiddleLeft��Top�ւ̔���
	if (y > BorderMiddleLeftY)
	{
		//MiddleLeft�ւ̔���
		if (x < BorderMiddleLeftX)
			return MIDDLE_LEFT;

		return TOP;
	}
	
	//MiddleRight�ւ̔���
	if (y > BorderMiddleRightY && x > BorderMiddleRightX)
	{
		return MIDDLE_RIGHT;
	}

	//LowerRight�ւ̔���
	if (x > BorderLowerRightX)
		return LOWER_RIGHT;

	return STAR_MAX;
}

/**************************************
�E���́��ɂ���Ƃ��̃p�b�h���͏���
***************************************/
int CheckInputLowerRight(float x, float y)
{
	const float BorderMiddleRightY = 0.7f;		//MiddleRight�ֈړ�����X�e�B�b�N��Y�l
	const float BorderMiddleRightX = 0.6f;		//MiddleRight�ֈړ�����X�e�B�b�N��X�l
	const float BorderMiddleLeftX = -0.3f;		//MiddleLeft�ֈړ�����X�e�B�b�N��X�l
	const float BorderMiddleLeftY = 0.3f;		//MiddleLeft�ֈړ�����X�e�B�b�N��Y�l
	const float BorderLowerLeftX = -0.9f;		//LowerLeft�ֈړ�����X�e�B�b�N��X�l

	//MiddleRight��Top�ւ̔���
	if (y > BorderMiddleRightY)
	{
		//MiddleRight�ւ̔���
		if (x > BorderMiddleRightX)
			return MIDDLE_RIGHT;

		return TOP;
	}

	//MiddleLeft�ւ̔���
	if (y > BorderMiddleLeftY && x < BorderMiddleLeftX)
	{
		return MIDDLE_LEFT;
	}

	//LowerLeft�ւ̔���
	if (x < BorderLowerLeftX)
		return LOWER_LEFT;

	return STAR_MAX;
}

/**************************************
�E��́��ɂ���Ƃ��̃p�b�h���͏���
***************************************/
int CheckInputMiddleRight(float x, float y)
{
	const float BorderTopY = 0.8f;				//Top�ֈړ�����X�e�B�b�N��Y�l
	const float BorderMiddleLeftX = -0.9f;		//MiddleLeft�ֈړ�����X�e�B�b�N��X�l
	const float BorderLowerLeftX = -0.1f;		//LowerLeft�ֈړ�����X�e�B�b�N��X�l
	const float BorderLowerLeftY = 0.0f;		//LowerLeft�ֈړ�����X�e�B�b�N��Y�l
	const float BorderLowerRightY = -0.1f;		//LowerRight�ֈړ�����X�e�B�b�N��Y�l

	//Top�ւ̔���
	if (y > BorderTopY)
		return TOP;

	//MiddleLeft�ւ̔���
	if (x < BorderMiddleLeftX)
		return MIDDLE_LEFT;

	//LowerLeft�ւ̔���
	if (x < BorderLowerLeftX && y < BorderLowerLeftY)
		return LOWER_LEFT;

	//LowerRight�ւ̔���
	if (y < BorderLowerRightY)
		return LOWER_RIGHT;

	return STAR_MAX;
}

/**************************************
�^�񒆂́��ɂ���Ƃ��̃p�b�h���͏���
***************************************/
int CheckInputCenter(float x, float y)
{
	const float BorderTopY = 0.9f;				//Top�ֈړ�����X�e�B�b�N��Y�l
	const float BorderLowerY = -0.5f;			//Lower�ֈړ�����X�e�B�b�N��Y�l
	const float BorderLowerRightX = 0.3f;		//LowerRight�ֈړ�����X�e�B�b�N��X�l
	const float BorderLowerLeftX = -0.3f;		//LowerLeft�ֈړ�����X�e�B�b�N��X�l
	const float BorderMiddleLeftX = -0.3f;		//MiddleLeft�ֈړ�����X�e�B�b�N��X�l
	const float BorderMiddleRightX = 0.3f;		//MiddleRight�ֈړ�����X�e�B�b�N��X�l

	//Top�ւ̔���
	if (y > BorderTopY)
		return TOP;

	//Lower�ւ̔���
	if (y < BorderLowerY)
	{
		//LowerRight�ւ̔���
		if (x > BorderLowerRightX)
			return LOWER_RIGHT;

		//LowerLeft�ւ̔���
		if (x < BorderLowerLeftX)
			return LOWER_LEFT;
	}

	//MiddleLeft�ւ̔���
	if (x < BorderMiddleLeftX)
	{
		return MIDDLE_LEFT;
	}

	//MiddleRight�ւ̔���
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
