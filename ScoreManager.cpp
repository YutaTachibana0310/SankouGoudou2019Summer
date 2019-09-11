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
static int currentCombo;
static int comboCaunta;
static GameSceneUIManager *viewerInstance;

/**************************************
マクロ定義
***************************************/

/**************************************
各処理が行われたときに呼ぶ関数オブジェクト
***************************************/
static std::function<void(int)> onAddComboEffect;
static std::function<void(void)> onClearCombo;

/**************************************
スコア加算処理
***************************************/
void SetAddScore(int n) {

	//スコア計算式
	//加算スコア = 素点(n) * (1.0f + コンボ * 0.05f)
	int addScore = (int)(n * (1.0f + currentCombo * 0.05f));

	currentStageScore += addScore;

	if(viewerInstance != NULL)
		viewerInstance->AddScore(addScore);
}

/**************************************
コンボ加算処理
***************************************/
void SetAddCombo(int n) {
	
	currentCombo += n;

	if (currentCombo % 5 == 0)
		comboCaunta++;

	if(viewerInstance != NULL)
		viewerInstance->AddCombo(n);

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
コンボクリア処理
***************************************/
void ClearCombo(void) {

	currentCombo = 0;
	comboCaunta = 0;
	
	if(viewerInstance != NULL)
		viewerInstance->ReSetCombo();

	Sound::GetInstance()->changepitch = 0;

	if (onClearCombo != NULL)
		onClearCombo();
}

/**************************************
スコア加算コールバック設定処理
***************************************/
void SetCallbackAddCombo(std::function<void(int)> callback)
{
	onAddComboEffect = callback;
}

/**************************************
コンボクリアコールバック設定処理
***************************************/
void SetCallbackClearCombo(std::function<void(void)> callback)
{
	onClearCombo = callback;
}

/**************************************
ゲームUIマネージャインスタンス設定処理
***************************************/
void SetGameScneeUIManagerInstance(GameSceneUIManager* instance)
{
	viewerInstance = instance;
}

/**************************************
スコア取得処理
***************************************/
int GetCurrentGameScore()
{
	return currentStageScore;
}

/**************************************
スコア設定処理
***************************************/
void SetCurrentGameScore(int score)
{
	currentStageScore = score;
}

/**************************************
コンボ設定処理
***************************************/
void SetCurrentCombo(int combo)
{
	currentCombo = combo;
}

/**************************************
諸々クリア処理
***************************************/
void ClearScoreManager()
{
	onAddComboEffect = NULL;
	onClearCombo = NULL;
	viewerInstance = NULL;
}