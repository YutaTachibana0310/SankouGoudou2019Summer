//=====================================
//
//�V���O���g������[Singleton.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "Singleton.h"

/**************************************
�O���[�o���ϐ�
***************************************/
const int MaxFinalizersSize = 256;
static  int numFinalizersSize = 0;
static SingletonFinalizer::FinalizerFunc finalizers[MaxFinalizersSize];

/**************************************
�V���O���g���j�������ǉ�
**************************************/
void SingletonFinalizer::AddFinalizer(FinalizerFunc func)
{
	assert(numFinalizersSize < MaxFinalizersSize);
	finalizers[numFinalizersSize++] = func;
}

/**************************************
�V���O���g���j��
**************************************/
void SingletonFinalizer::Finalize()
{
	for (int i = numFinalizersSize - 1; i >= 0; i--)
	{
		(*finalizers[i])();
	}

	numFinalizersSize = 0;
}