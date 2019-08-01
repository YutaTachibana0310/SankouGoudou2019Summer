//=============================================================================
//
// �X�e�[�W�N���A�e���b�v���� [stageClearTelop.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _STAGE_CLEAR_TELOP_H_
#define _STAGE_CLEAR_TELOP_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	ADRESS_TEXTURE_STAGE_CLEAR_TELOP	("data/TEXTURE/UI/telop/stageClearTelop.png")	// �ǂݍ��ރe�N�X�`���t�@�C����

#include "GameSceneUIManager.h"
#include "UIdrawer.h"

class Object;

/**************************************
�O���錾
***************************************/
class GameSceneUI;
class TelopBG;

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
class StageClearTelop :public GameSceneUI
{
public:
	Object *object;
	TelopBG *telopBG;
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�e���b�v�Z�b�g�֐�
	void SetStageClearTelop(void);
};


#endif
