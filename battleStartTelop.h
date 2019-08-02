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

#include "GameSceneUIManager.h"
#include "UIdrawer.h"

/**************************************
�O���錾
***************************************/
class Object;
class GameSceneUI;
class TelopBG;

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
class BattleStartTelop :public Object
{
public:
	Object*object;
	TelopBG*telopBG;
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�e���b�v�Z�b�g�֐�
	void SetBattleStartTelop(void);
};

#endif
