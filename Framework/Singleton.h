//=====================================
//
//シングルトンヘッダ[Singleton.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#include "../main.h"
#include <mutex>

/**************************************
SingletonFinalizerクラス
シングルトンの破棄を担当する
***************************************/
class SingletonFinalizer
{
public:
	typedef void(*FinalizerFunc)();

	//シングルトンのデストラクタを追加する
	static void AddFinalizer(FinalizerFunc func);

	//破棄処理
	static void Finalize();
};

/**************************************
Singletonテンプレートクラス
***************************************/
template <typename T>
class Singleton final
{
public:
	static T* GetInstance()
	{
		std::call_once(initFlag, Create);
		assert(instance);
		return instance;
	}

private:
	static void Create()
	{
		instance = new T;
		SingletonFinalizer::AddFinalizer(&Singleton<T>::Destroy);
	}

	static void Destroy()
	{
		delete instance;
		instance = nullptr;
	}

	static std::once_flag initFlag;
	static T* instance;
};

template <typename T> std::once_flag Singleton<T>::initFlag;
template <typename T> T* Singleton<T>::instance = nullptr;
#endif