//=====================================
//
//�X�e�[�g�V�[���w�b�_[IStateScene.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _STATESCENE_H_
#define _STATESCENE_H_

#include "main.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class IStateScene
{
public:
	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	IStateScene() {};
	virtual ~IStateScene() {};
};

#endif