//=====================================
//
// TitleCity.h
// 機能:タイトルの街背景
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _TITLECITY_H_
#define _TITLECITY_H_

#include "main.h"
#include "Framework\Polygon2D.h"

/**************************************
前方宣言
***************************************/

namespace Title
{
	/**************************************
	クラス定義
	***************************************/
	class CityBG : public Polygon2D
	{
	public:
		CityBG();

		void Update();

	private:
		float offsetU;
	};
}

#endif