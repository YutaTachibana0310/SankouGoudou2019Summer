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
#include "Framework\Vector3.h"
#include "LineTrailModel.h"

/**************************************
�O���[�o���ϐ�
***************************************/
static GameSceneUIManager* instanceUImanager;

/**************************************
�v���g�^�C�v�錾
***************************************/
int CheckStickInput(D3DXVECTOR3& stick, int current);

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
	//�X�e�B�b�N�̌X���x�N�g�����v�Z
	D3DXVECTOR3 stick = Vector3::Zero;
	stick.x = GetAxisX(0);
	stick.y = GetAxisY(0);

	//�X���[���Ȃ烊�^�[��
	if (stick == Vector3::Zero)
		return STAR_MAX;

	return CheckStickInput(stick, currentStar);
}

/*************************************
�p�b�h���͏���
***************************************/
int CheckStickInput(D3DXVECTOR3& stick, int current)
{
	float minAngle = 90.0f;
	int target = STAR_MAX;

	//�X�e�B�b�N�̌X���Ɉ�ԋ߂�����T��
	for (int i = 0; i < STAR_MAX; i++)
	{
		if (i == current)
			continue;

		D3DXVECTOR3 line = LineTrailModel::GetEdgePos(i) - LineTrailModel::GetEdgePos(current);
		float angle = fabsf(Vector3::Angle(stick, line));
		if (fabsf(angle) <= minAngle)
		{
			minAngle = angle;
			target = i;
		}
	}

	return target;
}

bool GetBomberInput()
{
	if (IsMouseRightTriggered())
		return true;

	if (GetKeyboardTrigger(DIK_SPACE) || GetKeyboardTrigger(DIK_LSHIFT))
		return true;

	if (IsShoulderButtonTriggerd())
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
	for (DWORD button = BUTTON_A; button <= BUTTON_X; button = button << 1)
	{
		if (IsButtonTriggered(0, button))
			return true;
	}

	return false;
}

bool IsShoulderButtonTriggerd()
{
	return IsButtonTriggered(0, BUTTON_Y) || IsButtonTriggered(0, BUTTON_Z);
}