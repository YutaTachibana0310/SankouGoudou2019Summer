//=====================================
//
//ボスUIマネージャヘッダ[BossUIManager.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BOSSUIMANAGER_H_
#define _BOSSUIMANAGER_H_

#include "main.h"

/**************************************
前方宣言
***************************************/
class WarningUI;

/**************************************
マクロ・列挙子定義
***************************************/

/**************************************
クラス定義
***************************************/
class BossUImanager
{
public:
	BossUImanager();
	~BossUImanager();

	void Update();
	void Draw();

	void SetWarning();

private:
	WarningUI *warning;
};

#endif