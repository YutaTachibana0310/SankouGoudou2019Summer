//=============================================================================
//
// ステートマシン処理 [IStateMachine.h]
// Author : 権頭
//
//=============================================================================
#ifndef _ISTATEMACHINE_H_
#define _ISTATEMACHINE_H_

#include "main.h"

#define STATE_CONTINUOUS	(0)		//ステートを続行する
#define STATE_FINISHED		(1)		//ステートは終了した

/*****************************************************
IStateMachineクラス
継承先でOnUpdate(), OnStart(), OnExit()を実装する
*****************************************************/
template <class T>
class IStateMachine {
public:
	virtual int OnUpdate(T *entity) = 0;
	virtual void OnStart(T *entity) = 0;
	virtual void OnExit(T *entity) = 0;
};

#endif