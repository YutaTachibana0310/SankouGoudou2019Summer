//=====================================
//
//�e���v���[�g�w�b�_[ObserveSubject.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _OBSEVESUBJECT_H_
#define _OBSEVESUBJECT_H_

#include <list>

/**************************************
�v���g�^�C�v�錾
***************************************/
class BaseObserver;

/**************************************
ObserveSubject�N���X
***************************************/
class ObserveSubject
{
public:
	void AddObserver(BaseObserver *observer);
	void RemoveObserver(BaseObserver *observer);

protected:
	void NotifyObservers();

	std::list<BaseObserver*> observers;
};

#endif