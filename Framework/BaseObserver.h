//=====================================
//
//�x�[�X�I�u�U�[�o�[�w�b�_[BaseObserver.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _BASEOBSERVER_H_
#define _BASEOBSERVER_H_

/**************************************
�}�N����`
***************************************/

/**************************************
�O���錾
***************************************/
class ObserveSubject;

/**************************************
BaseObserver�N���X
�p�����void OnNotified()���`����
***************************************/
class BaseObserver
{
public:
	virtual void OnNotified(ObserveSubject *notifier) = 0;
};

#endif