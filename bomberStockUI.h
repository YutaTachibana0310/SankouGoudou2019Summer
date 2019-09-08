//=============================================================================
//
// �{���X�g�b�N��ʏ��� [bomberStockUI.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _BOMBER_STOCK_H_
#define _BOMBER_STOCK_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_STOCKED_BOM_NUM (3)

/**************************************
�O���錾
***************************************/
class Object;
class RotateObject;
class Viewer3D;

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
class BomberStock
{
public:
	BomberStock();
	~BomberStock();

	void Update(void);
	void Draw(void);

	//�X�g�b�N���ꂽ�{���̐�
	int stockedBomNum;

private:
	RotateObject * bom[MAX_STOCKED_BOM_NUM];
	Object * bg;
	Viewer3D * viewer;
};

#endif
