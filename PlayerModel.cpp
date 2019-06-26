//=====================================
//
//プレイヤーモデル処理[PlayerModel.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "PlayerModel.h"
#include "star.h"

using namespace std;

/**************************************
マクロ定義
***************************************/
#define PLAYERMODEL_JUDGSTACK_LENGTH	(5)
#define PLAYERMODEL_MOVEQUEUE_LENGTH	(6)

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/

/**************************************
コンストラクタ
***************************************/
PlayerModel::PlayerModel()
{
	//一筆書きの正解を設定
	Judgement.resize(PLAYERMODEL_JUDGSTACK_LENGTH);
	Judgement[0] = TOP;
	Judgement[1] = LOWER_LEFT;
	Judgement[2] = MIDDLE_RIGHT;
	Judgement[3] = MIDDLE_LEFT;
	Judgement[4] = LOWER_RIGHT;

}

/**************************************
デストラクタ
***************************************/
PlayerModel::~PlayerModel()
{
	Judgement.clear();
	moveQueue.clear();
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
移動履歴のプッシュ
***************************************/
void PlayerModel::PushMoveStack(int num)
{
	//最大数であれば一番古い履歴を削除
	if (moveQueue.size() == PLAYERMODEL_MOVEQUEUE_LENGTH)
		moveQueue.pop_front();

	//プッシュ
	moveQueue.push_back(num);
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
	//一筆書きの画数に足りていなければリターン
	if (moveQueue.size() < PLAYERMODEL_MOVEQUEUE_LENGTH)
		return false;

	//一筆書きの開始位置のインデックスを検索
	auto itrStart = find(Judgement.begin(), Judgement.end(), moveQueue.back());
	size_t startIndex = distance(Judgement.begin(), itrStart);

	//反時計回りで検索
	bool res = _CheckOneStroke(startIndex);

	//成立していたらリターン
	if (res)
		return true;

	//判定用配列を逆転させ開始位置を検索
	reverse(Judgement.begin(), Judgement.end());
	itrStart = find(Judgement.begin(), Judgement.end(), moveQueue.back());
	startIndex = distance(Judgement.begin(), itrStart);

	//時計回りで検索
	res = _CheckOneStroke(startIndex);

	//判定用配列を元に戻してリターン	
	reverse(Judgement.begin(), Judgement.end());
	return res;
}

/**************************************
履歴クリア
***************************************/
void PlayerModel::Clear()
{
	moveQueue.clear();
	queue<int>().swap(inputQueue);
}

/**************************************
一筆書き判定（内部）
***************************************/
bool PlayerModel::_CheckOneStroke(size_t start)
{
	for (int i = 0; i < PLAYERMODEL_MOVEQUEUE_LENGTH; i++)
	{
		//対象のインデックスを計算
		int checkIndex = WrapAround(0, PLAYERMODEL_JUDGSTACK_LENGTH, start + i);

		//判定用配列と移動履歴がちがっていればreturn false
		if (Judgement[checkIndex] != moveQueue[i])
			return false;
	}

	//一筆書きと一致するので履歴をクリアしてreturn true
	//次の判定用に最後の履歴はプッシュしておく
	int lastMove = moveQueue.back();
	moveQueue.clear();
	moveQueue.push_back(lastMove);
	return true;
}

/**************************************
直近1件の軌跡の取得
***************************************/
bool PlayerModel::GetPlayerTrail(PlayerTrailModel *pOut)
{
	int queSize = moveQueue.size();
	if (queSize < 2)
		return false;
	
	*pOut = PlayerTrailModel(moveQueue[queSize - 1], moveQueue[queSize - 2]);
	return true;
}

/**************************************
全軌跡の取得
***************************************/
size_t PlayerModel::GetAllPlayerTrail(vector<PlayerTrailModel> *container)
{
	if (moveQueue.size() < 2)
		return 0;

	int modelCount = moveQueue.size() - 1;
	container->clear();
	container->resize(modelCount);

	for (int i = 0; i < modelCount; i++)
	{
		container->push_back(PlayerTrailModel(moveQueue[i + 1], moveQueue[i]));
	}

	return modelCount;
}