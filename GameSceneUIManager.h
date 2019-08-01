//=============================================================================
//
// Game�V�[��UI�Ǘ����� [GameSceneUIMaager.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _GAMESCENEUIMANAGER_H_
#define _GAMESCENEUIMANAGER_H_

#include "UIdrawer.h"

/**************************************
�O���錾
***************************************/
class Object;
class Guage;
class Combo;
class Cursor;
class Line;
class Score;
class Star;
class Trail;
class TelopBG;
class BattleStartTelop;
class StageClearTelop;

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
class GameSceneUI:public Object
{
public:
	Guage*guage;
	Combo*combo;
	Cursor*cursor;
	Line*line;
	Score*score;
	Star*star;
	Trail*trail;
	TelopBG*telopBG;
	BattleStartTelop*battleStartTelop;
	StageClearTelop*stageClearTelop;

	virtual void Init(void);
	virtual void Uninit(void);
	virtual void Update(HWND hwnd);
	virtual void Draw(void);
};

#endif

