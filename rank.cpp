#include "rank.h"
#include "starUI.h"
#include "scoreUI.h"
#include "savefile.h"
#include "scoreUI.h"
#include "GameSceneUIManager.h"

SCORERANK scorenumber[ARRAY_MAX];

//=============================================================================
// ランキング初期化処理
//=============================================================================
Rank::Rank()
{
	//ランキング数字側の処理
	for (int i = 0; i < RANK_MAX; i++) {

		number[i] = new CounterObject;

		number[i]->LoadTexture(ADRESS_TEXTURE_NUMBER_RANK);
		number[i]->MakeVertex();
		number[i]->position = numberPosition[i];
		number[i]->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		number[i]->size = SIZE_RANK;
		number[i]->SetColorObject(numberColor[i]);
	}

	//ランキングBGの処理
	for (int i = 0; i < RANK_MAX; i++) {

		bg[i] = new Object;

		bg[i]->LoadTexture(bgTexPath[i]);
		bg[i]->MakeVertex();
		bg[i]->position = bgPosition[i];
		bg[i]->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		bg[i]->size = SIZE_BG_RANK;

		bg[i]->SetColorObject(SET_COLOR_NOT_COLORED);
	}

	acceleration = { 0,0,0 };
	attraction = { 0,0,0 };
	dir = { 0,0,0 };
	target = { 0,0,0 };
	length = 0.0f;

	numberactive[0] = false;
	numberactive[1] = false;
	numberactive[2] = false;
	numberactive[3] = false;
	numberactive[4] = false;
	numberactive[5] = true;

	//バイナリファイルの読み込み
	LoadData();

	//ランキングソート実行
	RankSort();

	//ソート後のランキングを保存
	SaveData();
}

Rank::~Rank()
{
	for (int i = 0; i < RANK_MAX; i++)
	{
		delete number[i];
		number[i] = NULL;

		delete bg[i];
		bg[i] = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void Rank::Update(void) {

	for (int i = RANK_MAX; i >= 0;i--) {
		if (numberactive[i]) {
			dir = (bg[i]->position - D3DXVECTOR3(80,-10,0)) - number[i]->position;
			//正規化
			D3DXVec3Normalize(&dir, &dir);
			//ターゲット距離算出
			target = (bg[i]->position - D3DXVECTOR3(80, -10, 0)) - number[i]->position;
			length = D3DXVec3Length(&target);
			//ターゲットへ移動
			attraction = dir * 10;
			attraction += acceleration * (1 - length);

			number[i]->position += attraction;

			if (length <= 1.0f) {
				attraction = D3DXVECTOR3(0, 0, 0);
				numberactive[i] = false;
				if (i > 0) {
					numberactive[i - 1] = true;
				}
			}

		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void Rank::Draw(void) {

	for (int i = 0; i < RANK_MAX; i++) {
		bg[i]->Draw();
		bg[i]->SetVertex();
		for (int nCntPlace = 0; nCntPlace < PLACE_MAX; nCntPlace++)
		{
			int num;

			num = scorenumber[i].g_scorenumber % (int)(powf(BASE_NUMBER, (float)(PLACE_MAX - nCntPlace))) / (int)(powf(BASE_NUMBER, (float)(PLACE_MAX - nCntPlace - 1)));

			number[i]->Draw();
			number[i]->SetVertex(nCntPlace, INTERVAL_RANKING_NUMBER);
			number[i]->SetTexture(num, INTERVAL_NUMBER_TEXTURE);
		}

	}
}

void Rank::RankSort(void) {

	//前回分のマイスコアを初期化
	scorenumber[MYSCORE].g_scorenumber = NULL;

	//今回の分のスコアを配列の最後に代入
	gameSceneUIManager->SetScore(scorenumber[RANK_MAX].g_scorenumber);

	for (int i = 0; i <= RANK_MAX; i++) {

		//次の配列の値を取得
		for (int j = i + 1; j <= RANK_MAX; j++) {

			//前後の配列比較
			if (scorenumber[i].g_scorenumber < scorenumber[j].g_scorenumber) {

				//前の配列の数値が大きい場合入れ替え、tmpに一回退避
				tmp = scorenumber[i].g_scorenumber;

				//前の配列の数値を後ろの数値に代入
				scorenumber[i].g_scorenumber = scorenumber[j].g_scorenumber;

				//後ろの配列に退避した前の数値を代入
				scorenumber[j].g_scorenumber = tmp;
			}
		}
	}

	//今回の分のマイスコアを中心に
	gameSceneUIManager->SetScore(scorenumber[MYSCORE].g_scorenumber);
}

SCORERANK *GetRank() {
	return &scorenumber[0];
}
