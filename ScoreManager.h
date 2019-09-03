//=============================================================================
//
// スコアマネージャー [ScoreManager.h]
// Author : 渡邉良則
//
//=============================================================================
#ifndef _SCOREMANAGER_H
#define _SCOREMANAGER_H

class Score;
class GameSceneUIManager;


Score *score;
GameSceneUIManager *gameSceneUIManager;

void SetAddScore(int n);

void SetAddCombo(int n);

void ClearCombo(void);

#endif