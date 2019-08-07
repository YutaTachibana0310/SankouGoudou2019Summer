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

	AddScore(n);

}

/**************************************
�R���{���Z����
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
�R���{�N���A����
***************************************/
void ClearCombo(void) {

	SetCombo(0);
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