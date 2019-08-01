//=============================================================================
//
// スコアマネージャー [ScoreManager.cpp]
// Author : 渡邉良則
//
//=============================================================================

#include "ScoreManager.h"
#include "scoreUI.h"
#include "comboUI.h"
#include "sound.h"

static Score *score;
static Combo *combo;

void SetAddScore(int n) {

	score->AddScore(n);

}

void SetAddCombo(int n) {

	combo->AddCombo(n);

	Sound::GetInstance()->SetPlaySE(COMBOSE, true, 1.0f);
	Sound::GetInstance()->changepitch += n * 100;
	if (Sound::GetInstance()->changepitch > 1200) {
		Sound::GetInstance()->changepitch = 1200;
	}
	Sound::GetInstance()->SetPitchSE(COMBOSE, Sound::GetInstance()->changepitch);
}

void ClearCombo(void) {

	combo->SetCombo(0);
	Sound::GetInstance()->changepitch = 0;

}

