//=============================================================================
//
// InputController���� [InputController.cpp]
// Author : �n糗Ǒ�
//
//=============================================================================
#include "input.h"
#include "star.h"
#include "sound.h"

//�T�E���h�e�X�g�p
bool soundtest = false;
bool pausetest = false;
int changepitch = 0;

bool IsEntered(int m, HWND hWnd) {

	//�}�E�X�N���b�N�̌��o�����邩
	if (IsMouseLeftTriggered())
	{
		return IsStarSelected(m, hWnd);
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
	//�T�E���h�̍Đ�
	if (!soundtest) {
		//�Q�[���J�n�Ɠ����ɍĐ��A�t�F�[�h�C��
		Sound::GetInstance()->SetPlayBGM(GAMEBGM, true, 0.1f);
		Sound::GetInstance()->FadeIn(GAMEBGM, 10.0f, 1.0f, true);
	}
	else {
		//�t�F�[�h�A�E�g�̊J�n
		Sound::GetInstance()->FadeOut(GAMEBGM, 10.0f, 1.0f, true);
	}

	if (GetKeyboardTrigger(DIK_SPACE)) {
		//�悭����V���b�gSE�݂����ɍĐ�
		Sound::GetInstance()->SetPlaySE(TESTSE, true, 1.0f);
		Sound::GetInstance()->ChangeSEVolume(TESTSE, 1.0f);
	}
	if (GetKeyboardTrigger(DIK_O)) {

		soundtest = soundtest ? false : true;
	}
	if (GetKeyboardTrigger(DIK_P)) {
		//true�̏ꍇ�Q�[������SE�Đ�
		//false�̏ꍇ�̓|�[�Y����SE�Đ�
		pausetest = pausetest ? false : true;
		Sound::GetInstance()->SetPlaySE(ENTERSE, pausetest, 1.0f);
		Sound::GetInstance()->SetPitchSE(ENTERSE, 0);
		Sound::GetInstance()->ChangePauseSound(pausetest);
	}
	if (GetKeyboardTrigger(DIK_L)) {
		changepitch += 100;
		if (changepitch > 1200) {
			changepitch = 1200;
		}
		//�|�[�Y����SE���点�邩�e�X�g
		Sound::GetInstance()->SetPlaySE(ENTERSE, false, 1.0f);
		//�|�[�Y���̂݃s�b�`�̕ύX
		Sound::GetInstance()->SetPitchSE(ENTERSE, changepitch);

	}	

	if (GetKeyboardTrigger(DIK_K)) {

		changepitch -= 100;
		if (changepitch > 0) {
			changepitch = 0;
		}
		//�|�[�Y����SE���点�邩�e�X�g
		Sound::GetInstance()->SetPlaySE(ENTERSE, false, 1.0f);
		//�|�[�Y���̂݃s�b�`�̕ύX
		Sound::GetInstance()->SetPitchSE(ENTERSE, changepitch);
	}
}