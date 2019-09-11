//=============================================================================
//
// スコアマネージャー [ScoreManager.h]
// Author : 渡邉良則
//
//=============================================================================
#ifndef _SCOREMANAGER_H
#define _SCOREMANAGER_H

#include <functional>

class Score;
class GameSceneUIManager;

void SetAddScore(int n);

void SetAddCombo(int n);

void ClearCombo(void);

void SetGameScneeUIManagerInstance(GameSceneUIManager* instance);

int GetCurrentGameScore();
void SetCurrentGameScore(int score);
void SetCurrentCombo(int combo);

void SetCallbackAddCombo(std::function<void(int)> callback);
void SetCallbackClearCombo(std::function<void(void)> callbak);

void ClearScoreManager();

#endif