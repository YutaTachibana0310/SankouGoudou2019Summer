//=============================================================================
//
// �X�e�[�W�N���A�e���b�v���� [stageClearTelop.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _STAGE_CLEAR_TELOP_H_
#define _STAGE_CLEAR_TELOP_H_

/**************************************
�O���錾
***************************************/
class TelopObject;
class TelopBG;

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
class StageClearTelop
{
public:
	StageClearTelop();
	~StageClearTelop();

	void Update(void);
	void Draw(void);

	bool isStageClearTelopActivated = false;

private:
	TelopObject * stageClearTelop;
	TelopBG *telopBG;

};


#endif
