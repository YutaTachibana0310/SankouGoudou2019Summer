//=====================================
//
//バックグラウンドコントローラヘッダ[BackGroundController.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BACKGROUNDCONTROLLER_H_
#define _BACKGROUNDCONTROLLER_H_

#include "main.h"


#include <vector>

/**************************************
前方宣言
***************************************/
class BackGroundCity;

/**************************************
クラス定義
***************************************/
class BackGroundController
{
public:
	BackGroundController();
	~BackGroundController();

	void Init();
	void Uninit();
	void Update();
	void Draw();

private:
	std::vector<BackGroundCity*> cityContainer;

	void CreateCityContainer();

};

#endif