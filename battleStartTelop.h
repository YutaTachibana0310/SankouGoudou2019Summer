//=============================================================================
//
// �o�g���X�^�[�g�e���b�v���� [battleStartTelop.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _BATTLE_START_TELOP_H_
#define _BATTLE_START_TELOP_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	ADRESS_TEXTURE_BATTLE_START_TELOP	("data/TEXTURE/UI/telop/battleStartTelop.png")	// �ǂݍ��ރe�N�X�`���t�@�C����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBattleStartTelop(void);
void	UninitBattleStartTelop(void);
void	UpdateBattleStartTelop(void);
void	DrawBattleStartTelop(void);

#endif
