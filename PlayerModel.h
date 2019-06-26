//=====================================
//
//プレイヤーモデルヘッダ[PlayerModel.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _PLAYERMODEL_H_
#define _PLAYERMODEL_H_

#include "main.h"
#include <queue>
#include <vector>
#include <deque>
#include "PlayerTrailModel.h"

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

	void PushInput(int num);				//先行入力の保存
	void PushMoveStack(int num);			//移動履歴のプッシュ
	bool IsExistPrecedInput(int *pres);		//先行入力の確認
	bool CheckOneStroke();					//一筆書きの判定
	void Clear();							//先行入力、移動履歴のクリア

	bool GetPlayerTrail(PlayerTrailModel *pOut);						//プレイヤーの直近1件の軌跡の取得
	size_t GetAllPlayerTrail(std::vector<PlayerTrailModel> *contaier);	//プレイヤーの全軌跡を取得

private:
	std::vector<int> Judgement;				//一筆書きの正解配列
	std::queue<int> inputQueue;				//先行入力を保存するキュー
	std::deque<int> moveQueue;				//移動履歴

	bool _CheckOneStroke(size_t start);		//内部での一筆書き判定
};


#endif