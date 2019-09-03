//=============================================================================
//
// �X�R�A�}�l�[�W���[ [ScoreManager.cpp]
// Author : �n糗Ǒ�
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

/**************************************
�}�N����`
***************************************/

/**************************************
�e�������s��ꂽ�Ƃ��ɌĂԊ֐��I�u�W�F�N�g
***************************************/
static std::function<void(int)> onAddComboEffect;
static std::function<void(void)> onClearCombo;

/**************************************
�X�R�A���Z����
***************************************/
void SetAddScore(int n) {

	gameSceneUIManager->AddScore(n);

}

/**************************************
�R���{���Z����
***************************************/
void SetAddCombo(int n) {

	gameSceneUIManager->AddCombo(n);

	Sound::GetInstance()->SetPlaySE(COMBOSE, true, 1.0f);
	Sound::GetInstance()->changepitch += n * 100;
	if (Sound::GetInstance()->changepitch > 1200) {
		Sound::GetInstance()->changepitch = 1200;
	}
	Sound::GetInstance()->SetPitchSE(COMBOSE, Sound::GetInstance()->changepitch);

	if (onAddComboEffect != NULL)
		onAddComboEffect(n);
}

/**************************************
�R���{�N���A����
***************************************/
void ClearCombo(void) {

	gameSceneUIManager->ReSetCombo();
	Sound::GetInstance()->changepitch = 0;

	if (onClearCombo != NULL)
		onClearCombo();

}

/**************************************
�X�R�A���Z�R�[���o�b�N�ݒ菈��
***************************************/
void SetCallbackAddCombo(std::function<void(int)> callback)
{
	onAddComboEffect = callback;
}

/**************************************
�R���{�N���A�R�[���o�b�N�ݒ菈��
***************************************/
void SetCallbackClearCombo(std::function<void(void)> callback)
{
	onClearCombo = callback;
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
