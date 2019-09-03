//=============================================================================
//
// GameシーンUI管理処理 [GameSceneUIMaager.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _GAMESCENEUIMANAGER_H_
#define _GAMESCENEUIMANAGER_H_

/**************************************
前方宣言
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
	Line*line;
	Score*score;
	Star*star;
	Trail*trail;
	TelopBG*telopBG;
	BattleStartTelop*battleStartTelop;
	StageClearTelop*stageClearTelop;

	void Init(void);
	void Uninit(void);
	void Update(HWND hwnd);
	void Draw(void);

	//=============================================================================
	// コンボの加算（引数で受け取った値をコンボに加算する）
	//=============================================================================
	void AddCombo(int value)
	{
		combo->combo += value;

		if (value > 0)
		{
			combo->volumeUpEffectUsed = true;
		}
	}
	//=============================================================================
	// コンボのセット
	//=============================================================================
	void SetCombo(int num)
	{
		num  = combo->combo;
	}

	//=============================================================================
	// コンボのリセット
	//=============================================================================
	void ReSetCombo(void)
	{
		combo->combo = 0;
	}

	//=============================================================================
	// スコアの加算（引数で受け取った値をスコアに加算する）
	//=============================================================================
	void AddScore(int value)
	{
		score += value;

		// スコアが加算されたら行う処理
		if (value > 0)
		{
			// エフェクト有効化
			score->volumeUpEffectUsed = true;
		}
	}

	//=============================================================================
	// スコアのセット
	//=============================================================================
	void SetScore(int num)
	{
		num = score->score;
	}

	//=============================================================================
	// HPの加算（引数で受け取った値をHOに加算する）
	//=============================================================================
	void AddHp(float value)
	{
		guage->trueGuagePercentage += (value /= guage->maxHp);
	}

	//=============================================================================
	// ステージクリアテロップセット処理
	//=============================================================================
	void SetStageClearTelop(void)
	{
		stageClearTelop->isStageClearTelopActivated = true;
	}

	//=============================================================================
	// バトルスタートテロップセット処理
	//=============================================================================
	void SetBattleStartTelop(void)
	{
		battleStartTelop->isBattleStartTelopActivated = true;
	}

	//=============================================================================
	// スター座標ゲット処理
	//=============================================================================
	D3DXVECTOR3* GetStarPosition(void)
	{
		return star->GetStarPosition();
	}

	//=============================================================================
	// スター座標セット処理
	//=============================================================================
	void SetStarPosition(D3DXVECTOR3* pos)
	{
		pos = star->GetStarPosition();
	}


private:
	bool IsStarCursorOvered();
	void UpdateCursorColor();
};

#endif

