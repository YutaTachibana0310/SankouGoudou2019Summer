//=====================================
//
//プレイヤーモデル処理[PlayerModel.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "PlayerModel.h"
#include "starButtonUI.h"
#include "ScoreManager.h"

using namespace std;

/**************************************
マクロ定義
***************************************/
#define PLAYERMODEL_INPUTHISTORY_MAX	(15)		//入力履歴の最大保存件数
#define PLAYERMODEL_MOVEHISTORY_MAX		(PLAYERMODEL_INPUTHISTORY_MAX-1)	//移動履歴の最大保存件数

//一筆書きのパーツを表す列挙子
enum OneStrokeParts
{
	TopToLowerleft,
	LowerleftToMiddleright,
	MiddlerightToMiddleleft,
	MiddleleftToLowerright,
	LowerrightToTop,
	PartsMax
};

/**************************************
構造体定義
***************************************/

/**************************************
static変数
***************************************/
//一筆書きを構成するラインの集合
const LineTrailModel PlayerModel::OneStrokePatrs[OneStrokeParts::PartsMax] = {
	LineTrailModel(TOP, LOWER_LEFT),
	LineTrailModel(LOWER_LEFT, MIDDLE_RIGHT),
	LineTrailModel(MIDDLE_RIGHT, MIDDLE_LEFT),
	LineTrailModel(MIDDLE_LEFT, LOWER_RIGHT),
	LineTrailModel(LOWER_RIGHT, TOP)
};

/**************************************
コンストラクタ
***************************************/
PlayerModel::PlayerModel()
{

}

/**************************************
デストラクタ
***************************************/
PlayerModel::~PlayerModel()
{
	inputHistory.clear();
	queue<int>().swap(inputQueue);
}

/**************************************
先行入力の保存
***************************************/
void PlayerModel::PushInput(int num)
{
	inputQueue.push(num);
}

/**************************************
入力履歴のプッシュ
***************************************/
void PlayerModel::PushMoveStack(int num, bool canUpdate)
{
	//最大数であれば一番古い履歴を削除
	if (inputHistory.size() == PLAYERMODEL_INPUTHISTORY_MAX)
		inputHistory.pop_front();

	//プッシュ
	inputHistory.push_back(num);

	//移動履歴の更新
	if(canUpdate)
		UpdateMoveHistory();
}

/**************************************
移動履歴の確認
***************************************/
void PlayerModel::UpdateMoveHistory()
{
	//入力履歴が2件以上無いと移動履歴を構築できないためリターン
	if (inputHistory.size() < 2)
		return;
	
	//最大保存件数であれば一番古い履歴を削除
	if (moveHistory.size() == PLAYERMODEL_MOVEHISTORY_MAX)
		moveHistory.pop_front();

	//新しい移動履歴をプッシュ
	auto lastHistory = inputHistory.end() - 1;
	int current = *lastHistory;
	int prev = *(lastHistory - 1);
	moveHistory.push_back(LineTrailModel(current, prev));
}

/**************************************
先行入力の確認
***************************************/
bool PlayerModel::IsExistPrecedInput(int *res)
{
	if (inputQueue.size() == 0)
		return false;

	*res = inputQueue.front();
	inputQueue.pop();
	return true;
}

/**************************************
一筆書きの判定
***************************************/
bool PlayerModel::CheckOneStroke()
{
	//判定用ワーク
	int checkWork[OneStrokeParts::PartsMax];
	ZeroMemory(checkWork, sizeof(checkWork));

	//移動履歴すべてに対して一筆書きを構成するパーツかどうか判定
	for (auto& model : moveHistory)
	{
		for (int i = 0; i < OneStrokeParts::PartsMax; i++)
		{
			//一筆書きを構成するパーツであればカウントしてbreak
			if (model == OneStrokePatrs[i])
			{
				checkWork[i]++;
				break;
			}
		}
	}

	//一筆書きを構成するパーツが一つでも欠けていればreturn false
	for (int i = 0; i < OneStrokeParts::PartsMax; i++)
	{
		if (checkWork[i] == 0)
			return false;
	}

	//一筆書きが成立しているので履歴をクリアしてreturn true
	//最新の履歴だけはプッシュしておく
	int lastInput = inputHistory.back();
	inputHistory.clear();
	moveHistory.clear();
	inputHistory.push_back(lastInput);
	return true;
}

/**************************************
履歴クリア
***************************************/
void PlayerModel::Clear()
{
	inputHistory.clear();
	moveHistory.clear();
	queue<int>().swap(inputQueue);
	//ClearCombo();
}

/**************************************
直近1件の軌跡の取得
***************************************/
bool PlayerModel::GetPlayerTrail(LineTrailModel *pOut)
{
	if (inputHistory.size() < 2)
		return false;
	
	int start = *(inputHistory.end() - 1);
	int end = *(inputHistory.end() - 2);
	*pOut = LineTrailModel(start, end);
	return true;
}

/**************************************
全軌跡の取得
***************************************/
size_t PlayerModel::GetAllPlayerTrail(vector<LineTrailModel> *container)
{
	if (moveHistory.size() == 0)
		return 0;

	container->clear();
	container->resize(moveHistory.size());

	for (auto& model : moveHistory)
	{
		container->push_back(model);
	}

	return moveHistory.size();
}