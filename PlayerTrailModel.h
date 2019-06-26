//=====================================
//
//プレイヤートレイルモデルヘッダ[PlayerTrailModel.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _PLAYERTRAILMODEL_H_
#define _PLAYERTRAILMODEL_H_

#include "main.h"

/**************************************
マクロ定義
***************************************/

/**************************************
Class PlayerTrailModel
プレイヤーがどの位置からどの位置へ移動したかを表す
***************************************/
class PlayerTrailModel
{
public:
	PlayerTrailModel(int start, int end);
	PlayerTrailModel() {}

	int start;
	int end;
};


#endif