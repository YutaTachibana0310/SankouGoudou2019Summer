//=====================================
//
// TitleCity.h
// �@�\:�^�C�g���̊X�w�i
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _TITLECITY_H_
#define _TITLECITY_H_

#include "main.h"
#include "Framework\Polygon2D.h"

/**************************************
�O���錾
***************************************/

namespace Title
{
	/**************************************
	�N���X��`
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