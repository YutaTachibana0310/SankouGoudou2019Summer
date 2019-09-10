//=====================================
//
//プレイヤーモデルヘッダ[PlayerModel.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _PLAYERMODEL_H_
#define _PLAYERMODEL_H_

#include "main.h"
#include "LineTrailModel.h"

#include <queue>
#include <vector>
#include <deque>
#include <map>

/**************************************
マクロ定義
***************************************/

/**************************************
PlayerModelクラス
入力履歴や移動履歴をまとめる
***************************************/
class PlayerModel
{
public:
	PlayerModel();
	~PlayerModel();

	void PushInput(int num);						//先行入力の保存
	void PushMoveStack(int num, bool canUpdate);	//移動履歴のプッシュ
	bool IsExistPrecedInput(int *pres);				//先行入力の確認
	bool CheckOneStroke();							//一筆書きの判定
	void Clear();									//先行入力、移動履歴のクリア

	bool GetPlayerTrail(LineTrailModel *pOut);						//プレイヤーの直近1件の軌跡の取得
	size_t GetAllPlayerTrail(std::vector<LineTrailModel> *contaier);	//プレイヤーの全軌跡を取得
	bool Empty();									//履歴があるかどうか

private:
	std::queue<int> inputQueue;						//先行入力を保存するキュー
	std::deque<int> inputHistory;					//入力履歴
	std::deque<LineTrailModel> moveHistory;			//移動履歴

	void UpdateMoveHistory();						//移動履歴の更新

	static const LineTrailModel OneStrokePatrs[];	//一筆書きを構成するラインの集合

};

#endif