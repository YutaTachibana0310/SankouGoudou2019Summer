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

static int currentStageScore;
static Score *score;
static GameSceneUIManager *gameSceneUIManager;

void SetAddScore(int n) {

	gameSceneUIManager->AddScore(n);

}

void SetAddCombo(int n) {

	gameSceneUIManager->AddCombo(n);

	Sound::GetInstance()->SetPlaySE(COMBOSE, true, 1.0f);
	Sound::GetInstance()->changepitch += n * 100;
	if (Sound::GetInstance()->changepitch > 1200) {
		Sound::GetInstance()->changepitch = 1200;
	}
	Sound::GetInstance()->SetPitchSE(COMBOSE, Sound::GetInstance()->changepitch);
}

void ClearCombo(void) {

	gameSceneUIManager->ReSetCombo();
	Sound::GetInstance()->changepitch = 0;

}

void SetScoreIntance(Score *instance)
{
	score = instance;
}

void SetGameScneeUIManagerInstance(GameSceneUIManager* instance)
{
	gameSceneUIManager = instance;
}

int GetCurrentGameScore()
{
	return currentStageScore;
}

void SetCurrentGameScore(int score)
{
	currentStageScore = score;
}