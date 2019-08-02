//=============================================================================
//
// Game�V�[��UI�Ǘ����� [GameSceneUIMaager.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _GAMESCENEUIMANAGER_H_
#define _GAMESCENEUIMANAGER_H_

#include "UIdrawer.h"
#include "comboUI.h"

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
class ComboManager;

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
class GameSceneUI
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

	ComboManager *comboManager;

	void Init(void);
	void Uninit(void);
	void Update(HWND hwnd);
	void Draw(void);
};

class ComboManager:public Combo
{
public:
	void AddCombo(int value)
	{
		combo += value;
	}
	void SetCombo(int value)
	{
		combo = value;
	}
	void EnableEffect(bool enableEffect)
	{
		enableEffect = true;
	}
};

class CursorManager
{
public:

};

class GuageManager
{
public:

};

class ScoreManager
{
public:

};

class StarManager
{
public:

};

class TrailManager
{
public:

};

//�e���b�v
class BattleStartTelopManager
{
public:

};
class StageClearTelopManager
{
public:

};

class TelopBGManager
{
public:

};

#endif

