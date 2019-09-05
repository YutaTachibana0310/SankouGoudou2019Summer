//=====================================
//
//�X�J�C�{�b�N�X�w�b�_[SkyBox.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _SKYBOX_H_
#define _SKYBOX_H_

#include "main.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class SkyBox
{
public:
	SkyBox(D3DXVECTOR3 vtxSize, D3DXVECTOR2 texSize);
	virtual ~SkyBox();

	virtual void Draw();

	virtual void LoadTexture(const char* path);
	virtual void SetUV(float texU, float texV);

protected:
	Transform * transform;
	LPDIRECT3DTEXTURE9 texture;
	LPDIRECT3DVERTEXBUFFER9 vtxBuff;

	void MakeVertexBuffer(float width, float height, float depth);

	enum Const
	{
		FieldNum = 4,		//�ʂ̐�
	};
};

#endif