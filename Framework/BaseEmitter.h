//=====================================
//
//�e���v���[�g�w�b�_[BaseEmitter.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _BASEEMITTER_H_
#define _BASEEMITTER_H_

#include "../main.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class BaseEmitter
{
public:
	BaseEmitter();
	virtual ~BaseEmitter();

	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;

	bool IsActive();

	Transform transform;

protected:
	bool active;
	int cntFrame;
	int duration;
};

#endif