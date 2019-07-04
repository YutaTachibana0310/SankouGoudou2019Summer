//=====================================
//
//�x�[�X�G�~�b�^�w�b�_[BaseEmitter.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _BASEEMITTER_H_
#define _BASEEMITTER_H_

#include "../main.h"
#include <vector>
#include <memory>

/**************************************
�O���錾
***************************************/
class BaseParticle;

/**************************************
BaseEmitter�N���X
���p�����Init(), Uninit(), Update()����������
***************************************/
class BaseEmitter
{
public:
	BaseEmitter(D3DXVECTOR3 *pos);
	BaseEmitter();
	virtual ~BaseEmitter();

	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	bool active;

	Transform transform;

protected:
	int cntFrame;
	int duration;
};

#endif