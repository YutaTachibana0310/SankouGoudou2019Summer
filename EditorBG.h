//=====================================
//
//�G�f�B�^BG�w�b�_[EditorBG.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _EDITORBG_H_
#define _EDITORBG_H_

#include "main.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class EditorBG
{
public:
	EditorBG();
	~EditorBG();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	LPDIRECT3DTEXTURE9 texture;
	VERTEX_2D vtxWk[NUM_VERTEX];
};

#endif