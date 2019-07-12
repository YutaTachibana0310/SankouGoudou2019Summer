//=====================================
//
//ストップエネミーモデルヘッダ[StopEnemyModel.h]
//一時停止するタイプのエネミーモデル
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _CHANGEENEMYMODEL_H_
#define _CHANGEENEMYMODEL_H_

#include "main.h"
#include "EnemyModel.h"

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class ChangeEnemyModel : public EnemyModel
{
public:
	ChangeEnemyModel();
	~ChangeEnemyModel();

	void Init(LineTrailModel model);
	int Update();
};

#endif