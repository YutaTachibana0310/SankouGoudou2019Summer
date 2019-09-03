//=============================================================================
//
// ランキング処理 [rank.h]
// Author : 渡邉良則
//
//=============================================================================
#ifndef _RANK_H
#define _RANK_H

#include "main.h"
#include "UIdrawer.h"

#define	ADRESS_TEXTURE_NUMBER_RANK	"data/TEXTURE/UI/number.png"	// 読み込むテクスチャファイル名

#define MYSCORE (5)
#define RANK_MAX (6)
#define ARRAY_MAX (7)		//最大配列数
#define SIZE_RANK		(D3DXVECTOR3(30.0f,40.0f,0.0f))
#define SIZE_BG_RANK		(D3DXVECTOR3(210.0f,150.0f,0.0f))

class Rank;
class GameSceneUIManager;


typedef struct
{
	int g_scorenumber; //数字


} SCORERANK;

class Rank
{
public:
	Rank();
	~Rank();

	void Update(void);

	void Draw(void);

	void RankSort(void);


private:
	CounterObject *number[RANK_MAX];
	Object *bg[RANK_MAX];
	GameSceneUIManager *gameSceneUIManager;

	const char *bgTexPath[RANK_MAX]
	{
		"data/TEXTURE/UI/Result/rank1.jpg",
		"data/TEXTURE/UI/Result/rank2.jpg",
		"data/TEXTURE/UI/Result/rank3.jpg",
		"data/TEXTURE/UI/Result/rank4.jpg",
		"data/TEXTURE/UI/Result/rank5.jpg",
		"data/TEXTURE/UI/Result/myrank.jpg"
	};

	const D3DXVECTOR3 numberPosition[RANK_MAX]
	{
		D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 6.0f, 0.0),
		D3DXVECTOR3(SCREEN_WIDTH / 5.0f, SCREEN_HEIGHT / 5 * 2.0f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH / 5.0f, SCREEN_HEIGHT / 5 * 4.0f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH / 1.3f, SCREEN_HEIGHT / 5 * 4.0f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH / 1.3f, SCREEN_HEIGHT / 5 * 2.0f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH / 2.0f ,SCREEN_HEIGHT / 1.8f, 0.0f)
	};

	const D3DXCOLOR numberColor[RANK_MAX]
	{
		SET_COLOR_RED,
		SET_COLOR_PINK,
		SET_COLOR_RIGHTBLUE,
		SET_COLOR_NOT_COLORED,
		SET_COLOR_NOT_COLORED,
		SET_COLOR_ORANGE
	};

	const D3DXVECTOR3 bgPosition[RANK_MAX]
	{
		D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 80, SCREEN_HEIGHT / 6.0f + 1000, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH / 5.0f - 1500, SCREEN_HEIGHT / 5 * 2.0f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH / 5.0f - 1500, SCREEN_HEIGHT / 5 * 4.0f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH / 1.3f + 1500, SCREEN_HEIGHT / 5 * 4.0f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH / 1.3f + 1500, SCREEN_HEIGHT / 5 * 2.0f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 80 ,SCREEN_HEIGHT / 1.8f + 10, 0.0f)
	};

	int	tmp;//ソート用の変数

    //数字の移動処理
	D3DXVECTOR3 acceleration;
	D3DXVECTOR3 attraction;
	bool numberactive[RANK_MAX];
	D3DXVECTOR3 dir;
	D3DXVECTOR3 target;
	float length;
};


#endif
