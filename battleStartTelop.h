//=============================================================================
//
// �o�g���X�^�[�g�e���b�v���� [battleStartTelop.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _BATTLE_START_TELOP_H_
#define _BATTLE_START_TELOP_H_

/**************************************
�O���錾
***************************************/
class TelopObject;
class TelopBG;

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
class BattleStartTelop
{
public:
	BattleStartTelop();
	~BattleStartTelop();

	void Update(void);
	void Draw(void);

	bool isBattleStartTelopActivated = false;

private:
	TelopObject * battleStartTelop;
	TelopBG*telopBG;
};

#endif
