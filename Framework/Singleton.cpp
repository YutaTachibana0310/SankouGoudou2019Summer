//=====================================
//
//シングルトン処理[Singleton.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "Singleton.h"

/**************************************
グローバル変数
***************************************/
const int MaxFinalizersSize = 256;
static  int numFinalizersSize = 0;
static SingletonFinalizer::FinalizerFunc finalizers[MaxFinalizersSize];

/**************************************
シングルトン破棄処理追加
**************************************/
void SingletonFinalizer::AddFinalizer(FinalizerFunc func)
{
	assert(numFinalizersSize < MaxFinalizersSize);
	finalizers[numFinalizersSize++] = func;
}

/**************************************
シングルトン破棄
**************************************/
void SingletonFinalizer::Finalize()
{
	for (int i = numFinalizersSize - 1; i >= 0; i--)
	{
		(*finalizers[i])();
	}

	numFinalizersSize = 0;
}