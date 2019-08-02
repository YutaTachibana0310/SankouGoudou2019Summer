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
#include "GameSceneUIManager.h"


//void SetAddScore(int n) {
//
//	score->AddScore(n);
//
//}
//
//void SetAddCombo(int n) {
//
//	comboManager->AddCombo(n);
//
//	Sound::GetInstance()->SetPlaySE(COMBOSE, true, 1.0f);
//	Sound::GetInstance()->changepitch += n * 100;
//	if (Sound::GetInstance()->changepitch > 1200) {
//		Sound::GetInstance()->changepitch = 1200;
//	}
//	Sound::GetInstance()->SetPitchSE(COMBOSE, Sound::GetInstance()->changepitch);
//}
//
//void ClearCombo(void) {
//
//	comboManager->SetCombo(0);
//	Sound::GetInstance()->changepitch = 0;
//
//}

