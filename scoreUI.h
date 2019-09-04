//=============================================================================
//
// スコア処理 [score.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	INTERVAL_NUMBER	(80.0f)				// スコア数字の表示間隔
#define	INTERVAL_RANKING_NUMBER	(50.0f)		// スコア数字の表示間隔（ランキング用）
#define	INTERVAL_NUMBER_TEXTURE	(0.1f)	// テクスチャテクスチャ内のスコア数字の表示間隔
#define	PLACE_MAX		(4)					// スコアの桁数
#define BASE_NUMBER		(10)				// 進数
#define VOLUME_ZOOM		(30.0f)
#define SIZE_NUMBER_SCORE		(D3DXVECTOR3(30.0f,50.0f,0.0f))
#define SIZE_BG_SCORE	(D3DXVECTOR3(160.0f,80.0f,0.0f))

#define POSITION_NUMBER_SCORE	(D3DXVECTOR3(SCREEN_WIDTH / 10 * 0.50f, SCREEN_HEIGHT / 10 * 1, 0.0f))
#define POSITION_BG_SCORE	(D3DXVECTOR3(SCREEN_WIDTH / 10 * 1.0f, SCREEN_HEIGHT / 10 * 1, 0.0f))

/**************************************
前方宣言
***************************************/
class CounterObject;
class Object;

//*****************************************************************************
// 構造体定義
//*****************************************************************************
class Score
{
public:
	Score();
	~Score();

	int	score;		// スコア
	int	score_max;

	float radian;
	bool volumeUpEffectUsed;

	void Update(void);
	void Draw(void);

private:
	Object * bg;
	CounterObject * counter;
	void VolumeUpEffect(void);
};

#endif
