//=============================================================================
//
// �X�R�A�}�l�[�W���[ [ScoreManager.cpp]
// Author : �n糗Ǒ�
//
//=============================================================================

#include "ScoreManager.h"
#include "scoreUI.h"
#include "comboUI.h"

void SetAddScore(int n) {

	AddScore(n);

}

void SetAddCombo(int n) {

	AddCombo(n);
}

void ClearCombo(void) {

	SetCombo(0);

}

int GetHiScore(void) {

	return SetScore();
}
