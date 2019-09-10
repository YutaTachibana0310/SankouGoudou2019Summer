//=====================================
//
// Logo.h
// 機能:タイトルロゴ表示
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _TACHIBANA_TITLELOGO_H_
#define _TACHIBANA_TITLELOGO_H_

#include "main.h"
#include "Framework\Polygon2D.h"
#include <vector>

namespace Title
{
	/**************************************
	前方宣言
	***************************************/
	class LogoParts;

	/**************************************
	Logoクラス
	***************************************/
	class Logo
	{
	public:
		Logo();
		~Logo();

		void Update();
		void Draw();

	private:
		std::vector<LogoParts*> logoContainer;
		Polygon2D *bg;
		int cntFrame;

		const int MoveStartTiming = 30;
		const int MoveDuration = 30;
		const float InitOffsetX = 1000.0f;
	};

	/**************************************
	LogoPartsクラス
	***************************************/
	class LogoParts : public Polygon2D
	{
	public:
		enum ID
		{
			City,
			Star,
			Liner,
			Max
		};

		LogoParts(ID id);

		void Update();

		void Move(D3DXVECTOR3 offset, int duration);

		static const D3DXVECTOR2 Size[];

	private:
		int cntFrame;
		int moveDuration;

		D3DXVECTOR3 moveTarget;
		D3DXVECTOR3 startPos;
	};
}

#endif