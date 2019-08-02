//=============================================================================
//
// �e���b�v�w�i���� [telopBG.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _TELOP_BG_H_
#define _TELOP_BG_H_
#include "UIdrawer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	ADRESS_TEXTURE_TELOP_BG	("data/TEXTURE/UI/telop/telopBG.png")	// �ǂݍ��ރe�N�X�`���t�@�C����

#include "GameSceneUIManager.h"
#include "UIdrawer.h"

class Object;

/**************************************
�O���錾
***************************************/
class GameSceneUI;

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
class TelopBG :public Object
{
public:
	Object *object;
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void AvctivateTelopBGOpen(void);
	void AvctivateTelopBGClose(void);

	bool GetTelopBGOpenActive(void);
	bool GetTelopBGCloseActive(void);

private:
	void OpenTelopBG(void);
	void CloseTelopBG(void);

	void SetEasingValueTelopBGOpen(void);
	void SetEasingValueTelopBGClose(void);
};

#endif
