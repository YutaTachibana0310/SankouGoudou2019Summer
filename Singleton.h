//=====================================
//
//�V���O���g���w�b�_[Singleton.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#include "main.h"
#include <mutex>

/**************************************
SingletonFinalizer�N���X
�V���O���g���̔j����S������
***************************************/
class SingletonFinalizer
{
public:
	typedef void(*FinalizerFunc)();

	//�V���O���g���̃f�X�g���N�^��ǉ�����
	static void AddFinalizer(FinalizerFunc func);

	//�j������
	static void Finalize();
};

/**************************************
Singleton�e���v���[�g�N���X
***************************************/
template <typename T>
class singleton final
{
public:
	static T& GetInstance()
	{
		std::call_once(initFlag, create);
		asset(instance);
		return *instance;
	}

private:
	static void Create()
	{
		instance = new T;
		SingletonFinalizer::AddFinalizer(&singleton<T>::Destroy);
	}

	static void Destroy()
	{
		delete instance;
		instance = nullptr;
	}

	static std::once_flag initFlag;
	static T* instance;
};

template <typename T> std::once_flag singleton<T>::initFlag;
template <typename T> T* singleton<T>::instance = nullptr;
#endif