//=============================================================================
//
// �X�R�A�}�l�[�W���[ [ScoreManager.h]
// Author : �n糗Ǒ�
//
//=============================================================================
#ifndef _SCOREMANAGER_H
#define _SCOREMANAGER_H

class Score;
class GameSceneUIManager;


void SetAddScore(int n);

void SetAddCombo(int n);

void ClearCombo(void);

void SetScoreIntance(Score *instance);
void SetGameScneeUIManagerInstance(GameSceneUIManager* instance);

int GetCurrentGameScore();
void SetCurrentGameScore(int score);
#endif