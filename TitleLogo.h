//=====================================
//
// Logo.h
// �@�\:�^�C�g�����S�\��
// Author:GP12B332 21 ���ԗY��
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
	�O���錾
	***************************************/
	class LogoParts;

	/**************************************
	Logo�N���X
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
	LogoParts�N���X
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