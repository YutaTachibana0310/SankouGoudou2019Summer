//=============================================================================
//
// �X�R�A�}�l�[�W���[ [ScoreManager.h]
// Author : �n糗Ǒ�
//
//=============================================================================
#ifndef _SCOREMANAGER_H
#define _SCOREMANAGER_H

#include <functional>

void SetAddScore(int n);

void SetAddCombo(int n);

void ClearCombo(void);

void SetCallbackAddCombo(std::function<void(int)> callback);
void SetCallbackClearCombo(std::function<void(void)> callbak);

#endif