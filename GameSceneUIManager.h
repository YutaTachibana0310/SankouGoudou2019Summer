//=============================================================================
//
// GameシーンUI管理処理 [GameSceneUIMaager.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _GAMESCENEUIMANAGER_H_
#define _GAMESCENEUIMANAGER_H_

#include <vector>

/**************************************
前方宣言
***************************************/
class Object;
class Guage;
class Combo;
class Cursor;
class Score;
class StarButton;
class Trail;
class TelopBG;
class BattleStartTelop;
class StageClearTelop;
class BomberStock;

//*****************************************************************************
// 構造体定義
//*****************************************************************************
class GameSceneUIManager
{
public:
	GameSceneUIManager();
	~GameSceneUIManager();

	Guage*guage;
	Combo*combo;
	Cursor*cursor;
	Score*score;
	StarButton*starButton;
	Trail*trail;
	TelopBG*telopBG;
	BattleStartTelop*battleStartTelop;
	StageClearTelop*stageClearTelop;
	BomberStock *bomberStock;

	void Init(void);
	void Uninit(void);
	void Update(HWND hwnd);
	void Draw(void);

	void AddCombo(int value);
	void SetCombo(int num);
	void ReSetCombo(void);
	void AddScore(int value);
	void SetScore(int num);
	void SetStageClearTelop(void);
	void SetBattleStartTelop(void);
	void GetStarPosition(std::vector<D3DXVECTOR3>& out);
	void SetHPGuage(float percentage);
	void SetBomberStock(int stockedBomNum, bool isCharging);

	/* 9/3 立花追加 */
	int IsStarSelected();		//スターボタンの入力確認

private:
	bool IsStarCursorOvered();
	void UpdateCursorColor();
};

#endif

