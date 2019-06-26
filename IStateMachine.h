//=============================================================================
//
// �X�e�[�g�}�V������ [IStateMachine.h]
// Author : ����
//
//=============================================================================
#ifndef _ISTATEMACHINE_H_
#define _ISTATEMACHINE_H_

#include "main.h"

#define STATE_CONTINUOUS	(0)		//�X�e�[�g�𑱍s����
#define STATE_FINISHED		(1)		//�X�e�[�g�͏I������

template <class T>
class IStateMachine {
public:
	virtual int OnUpdate(T *entity) = 0;
	virtual void OnStart(T *entity) = 0;
	virtual void OnExit(T *entity) = 0;
};

#endif