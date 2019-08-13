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

	AddScore(n);

}

/**************************************
コンボ加算処理
***************************************/
void SetAddCombo(int n) {

	AddCombo(n);

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
コンボクリア処理
***************************************/
void ClearCombo(void) {

	SetCombo(0);
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