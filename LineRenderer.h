//=====================================
//
//���C�������_���[�w�b�_[LineRenderer.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _LINERENDERER_H_
#define _LINERENDERER_H_

#include "main.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class LineRenderer
{
public:
	LineRenderer();
	~LineRenderer();

	void Init(D3DXVECTOR3 *right, D3DXVECTOR3 *left, float width);
	void Draw();
	void SetRightPos(D3DXVECTOR3 *pos);
	void SetLeftPos(D3DXVECTOR3 *pos);
	void SetColor(D3DXCOLOR color);

private:
	LPDIRECT3DVERTEXBUFFER9 vtxBuff;
	D3DXVECTOR3 vtxUp;
	float width;
};

#endif