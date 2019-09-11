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
static int currentCombo;
static int comboCaunta;
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

	//�X�R�A�v�Z��
	//���Z�X�R�A = �f�_(n) * (1.0f + �R���{ * 0.05f)
	int addScore = (int)(n * (1.0f + currentCombo * 0.05f));

	currentStageScore += addScore;
	gameSceneUIManager->AddScore(addScore);
}

/**************************************
�R���{���Z����
***************************************/
void SetAddCombo(int n) {
	
	currentCombo += n;

	if (currentCombo % 5 == 0)
		comboCaunta++;

	gameSceneUIManager->AddCombo(n);

	Sound::GetInstance()->SetPlaySE(COMBOSE, true, (Sound::GetInstance()->changevol / 7.0f));
	Sound::GetInstance()->changepitch = comboCaunta * 100;
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

	currentCombo = 0;
	comboCaunta = 0;
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

void SetCurrentCombo(int combo)
{
	currentCombo = combo;
}