//=====================================
//
//ステージモデルヘッダ[StageModel.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _STAGEMODEL_H_
#define _STAGEMODEL_H_

#include "main.h"
#include "picojson\picojson.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class StageModel
{
public:
	int frame;					//何フレーム目に生成されるか
	std::string type;			//生成するエネミーのタイプ
	picojson::object data;		//エネミーデータ

	StageModel(int frame, std::string type, picojson::object data)
	{
		this->frame = frame;
		this->type = type;
		this->data = data;
	}

	StageModel()
	{

	}

	~StageModel()
	{

	}
};

#endif