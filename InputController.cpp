//=============================================================================
//
// InputController処理 [InputController.cpp]
// Author : 渡邉良則
//
//=============================================================================
#include "input.h"
#include "star.h"
#include "sound.h"

//サウンドテスト用
bool soundtest = false;
bool pausetest = false;
int changepitch = 0;

bool IsEntered(int m, HWND hWnd) {

	//マウスクリックの検出があるか
	if (IsMouseLeftTriggered())
	{
		return IsStarSelected(m, hWnd);
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
	//サウンドの再生
	if (!soundtest) {
		//ゲーム開始と同時に再生、フェードイン
		Sound::GetInstance()->SetPlayBGM(GAMEBGM, true, 0.1f);
		Sound::GetInstance()->FadeIn(GAMEBGM, 10.0f, 1.0f, true);
	}
	else {
		//フェードアウトの開始
		Sound::GetInstance()->FadeOut(GAMEBGM, 10.0f, 1.0f, true);
	}

	if (GetKeyboardTrigger(DIK_SPACE)) {
		//よくあるショットSEみたいに再生
		Sound::GetInstance()->SetPlaySE(TESTSE, true, 1.0f);
		Sound::GetInstance()->ChangeSEVolume(TESTSE, 1.0f);
	}
	if (GetKeyboardTrigger(DIK_O)) {

		soundtest = soundtest ? false : true;
	}
	if (GetKeyboardTrigger(DIK_P)) {
		//trueの場合ゲーム中にSE再生
		//falseの場合はポーズ中にSE再生
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
		//ポーズ中にSEが鳴らせるかテスト
		Sound::GetInstance()->SetPlaySE(ENTERSE, false, 1.0f);
		//ポーズ中のみピッチの変更
		Sound::GetInstance()->SetPitchSE(ENTERSE, changepitch);

	}	

	if (GetKeyboardTrigger(DIK_K)) {

		changepitch -= 100;
		if (changepitch > 0) {
			changepitch = 0;
		}
		//ポーズ中にSEが鳴らせるかテスト
		Sound::GetInstance()->SetPlaySE(ENTERSE, false, 1.0f);
		//ポーズ中のみピッチの変更
		Sound::GetInstance()->SetPitchSE(ENTERSE, changepitch);
	}
}