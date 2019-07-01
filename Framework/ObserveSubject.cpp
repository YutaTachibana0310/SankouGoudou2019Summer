//=====================================
//
//�I�u�U�[�u�T�u�W�F�N�g����[ObserveSubject.cpp]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "ObserveSubject.h"
#include "BaseObserver.h"

using namespace std;

/**************************************
�}�N����`
***************************************/

/**************************************
�\���̒�`
***************************************/

/**************************************
�I�u�U�[�o�[�o�^����
***************************************/
void ObserveSubject::AddObserver(BaseObserver *observer)
{
	//�d���m�F
	auto checkResult = find(observers.begin(), observers.end(), observer);
	if (checkResult != observers.end())
		return;

	//�o�^
	observers.push_back(observer);
}

/**************************************
�I�u�U�[�o�[�폜����
***************************************/
void ObserveSubject::RemoveObserver(BaseObserver *observer)
{
	//�o�^�m�F
	auto checkResult = find(observers.begin(), observers.end(), observer);
	if (checkResult == observers.end())
		return;

	//�폜
	observers.remove(observer);
}

/**************************************
�I�u�U�[�o�[�ʒm����
***************************************/
void ObserveSubject::NotifyObservers()
{
	for (BaseObserver *observer : observers)
	{
		observer->OnNotified(this);
	}
}
