//=============================================================================
//
// ステートマシン処理 [IStateMachine.h]
// Author : 権頭
//
//=============================================================================
#ifndef _ISTATEMACHINE_H_
#define _ISTATEMACHINE_H_

#include "main.h"


template <class T>
class IStateMachine {
public:
	virtual void OnUpdate(T *entity) = 0;
	virtual void OnStart(T *entity) = 0;
	virtual void OnExit(T *entity) = 0;
};

#endif