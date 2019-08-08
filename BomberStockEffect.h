//=====================================
//
//�{���o�[�X�g�b�N�G�t�F�N�g�w�b�_[BomberStockEffect.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _BOMBERSTOCKEFFECT_H_
#define _BOMBERSTOCKEFFECT_H_

#include "main.h"
#include "Framework\BoardPolygon.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class BomberStockEffect
{
public:
	BomberStockEffect();
	~BomberStockEffect();

	void Init();
	void Update();
	void Draw();

	Transform transform;

private:
	bool active;
	int cntFrame;
	BoardPolygon* polygon;
};

#endif