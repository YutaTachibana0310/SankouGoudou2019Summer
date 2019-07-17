#include "rank.h"
#include "starUI.h"
#include "scoreUI.h"
#include "savefile.h"
#include "scoreUI.h"

SCORERANK scorerank[ARRAY_MAX];
OBJECT rank[RANK_MAX];
OBJECT rankBGParts[RANK_MAX];
//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
int	tmp;	//ソート用の変数

//=============================================================================
// ランキング初期化処理
//=============================================================================
HRESULT InitRank(void) {

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//ランキング数字側の処理
	for (int i = 0; i < RANK_MAX; i++) {

		LoadTexture(pDevice, ADRESS_TEXTURE_NUMBER_RANK, &rank[i]);
		InitialTexture(&rank[i]);
		MakeVertexObject(&rank[i]);
		rank[i].rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		rank[i].size = SIZE_RANK;

	}

	// 座標
	rank[TOP].position = POSITION_RANK_TOP;
	rank[MIDDLE_LEFT].position = POSITION_RANK_MIDDLE_LEFT;
	rank[LOWER_LEFT].position = POSITION_RANK_MIDDLE_RIGHT;
	rank[LOWER_RIGHT].position = POSITION_RANK_LOWER_LEFT;
	rank[MIDDLE_RIGHT].position = POSITION_RANK_LOWER_RIGHT;
	rank[CENTER].position = POSITION_RANK_CENTER;

	//　色設定
	SetColorObject(&rank[TOP], SET_COLOR_YELLOW);
	SetColorObject(&rank[MIDDLE_LEFT], SET_COLOR_PINK);
	SetColorObject(&rank[LOWER_LEFT], SET_COLOR_RIGHTBLUE);
	SetColorObject(&rank[LOWER_RIGHT], SET_COLOR_NOT_COLORED);
	SetColorObject(&rank[MIDDLE_RIGHT], SET_COLOR_NOT_COLORED);
	SetColorObject(&rank[CENTER], SET_COLOR_ORANGE);

	//ランキングBGの処理
	LoadTexture(pDevice, ADRESS_TEXTURE_BG_RANK1, &rankBGParts[0]);
	LoadTexture(pDevice, ADRESS_TEXTURE_BG_RANK2, &rankBGParts[1]);
	LoadTexture(pDevice, ADRESS_TEXTURE_BG_RANK3, &rankBGParts[2]);
	LoadTexture(pDevice, ADRESS_TEXTURE_BG_RANK4, &rankBGParts[3]);
	LoadTexture(pDevice, ADRESS_TEXTURE_BG_RANK5, &rankBGParts[4]);

	for (int i = 0; i < RANK_MAX; i++) {
		InitialTexture(&rankBGParts[i]);
		MakeVertexObject(&rankBGParts[i]);
		rankBGParts[i].rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		rankBGParts[i].size = SIZE_BG_RANK;

		rankBGParts[i].position = rank[i].position;
		SetColorObject(&rankBGParts[i], SET_COLOR_NOT_COLORED);

	}

	//バイナリファイルの読み込み
	LoadData();

	//ランキングソート実行
	RankSort();

	//ソート後のランキングを保存
	SaveData();



	return S_OK;
}

//=============================================================================
// ランキング終了処理
//=============================================================================
void UninitRank(void) {

	for (int i = 0; i < RANK_MAX; i++)
	{
		ReleaseTexture(&rank[i]);
		ReleaseTexture(&rankBGParts[i]);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawRank(void) {

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < RANK_MAX; i++) {
		DrawObject(pDevice, rankBGParts[i]);
		SetVertexObject(&rankBGParts[i]);
		for (int nCntPlace = 0; nCntPlace < PLACE_MAX; nCntPlace++)
		{
			int number;

			number = scorerank[i].g_scorerank % (int)(powf(BASE_NUMBER, (float)(PLACE_MAX - nCntPlace))) / (int)(powf(BASE_NUMBER, (float)(PLACE_MAX - nCntPlace - 1)));

			DrawObject(pDevice, rank[i]);
			SetVertexCounter(&rank[i], nCntPlace, INTERVAL_RANKING_NUMBER);
			SetTextureCounter(&rank[i], number, INTERVAL_NUMBER_TEXTURE);
		}

	}
}

void RankSort(void) {

	//前回分のマイスコアを初期化
	scorerank[MYSCORE].g_scorerank = NULL;

	//今回の分のスコアを配列の最後に代入
	scorerank[RANK_MAX].g_scorerank = SetScore();

	for (int i = 0; i <= RANK_MAX; i++) {

		//次の配列の値を取得
		for (int j = i + 1; j <= RANK_MAX; j++) {

			//前後の配列比較
			if (scorerank[i].g_scorerank < scorerank[j].g_scorerank) {

				//前の配列の数値が大きい場合入れ替え、tmpに一回退避
				tmp = scorerank[i].g_scorerank;

				//前の配列の数値を後ろの数値に代入
				scorerank[i].g_scorerank = scorerank[j].g_scorerank;

				//後ろの配列に退避した前の数値を代入
				scorerank[j].g_scorerank = tmp;

			}
		}
	}

	//今回の分のマイスコアを中心に
	scorerank[MYSCORE].g_scorerank = SetScore();


}

SCORERANK *GetRank() {
	return &scorerank[0];
}





