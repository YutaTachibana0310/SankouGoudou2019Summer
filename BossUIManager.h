//=====================================
//
//ボスUIマネージャヘッダ[BossUIManager.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BOSSUIMANAGER_H_
#define _BOSSUIMANAGER_H_

#include "main.h"
#include <vector>

/**************************************
前方宣言
***************************************/
class WarningUI;
class BossBulletGuide;
class LineTrailModel;

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
	void SetBulletGuide(LineTrailModel& model);

private:
	WarningUI *warning;
	std::vector<BossBulletGuide*> bulletGuide;
};

#endif