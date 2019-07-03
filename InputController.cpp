//=============================================================================
//
// InputController���� [InputController.cpp]
// Author : �n糗Ǒ�
//
//=============================================================================
#include "input.h"
#include "star.h"
#include "sound.h"
#include "Game.h"
#include "masktex.h"


//�V�[���`�F���W�p
Scene counta = SceneTitle;
bool scenechange = false;
int changecounta = 0;

bool IsEntered(int m, HWND hWnd) {

	//�}�E�X�N���b�N�̌��o�����邩
	if (IsMouseLeftTriggered())
	{
		return IsSelected(m, hWnd);
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

void InputSound() {



}

void SceneChange() {

	if (GetKeyboardTrigger(DIK_RETURN)) {
		
		switch (counta)
		{
		case SceneTitle:
			counta = SceneGame;
			break;
		case SceneGame:
			counta = SceneResult;
			break;
		case SceneResult:
			counta = SceneTitle;
			break;
		}
		scenechange = true;

		SceneChangeFlag(true);
	}

	

	if (scenechange) {

		changecounta++;

		if(changecounta >= 60){

			ChangeScene(counta);
			scenechange = false;
			changecounta = 0;

		}

	}
	
	
}