//=====================================
//
//�R���C�_�[�I�u�U�[�o�[�w�b�_[ColliderObserver.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _COLLIDEROBSERVER_H_
#define _COLLIDEROBSERVER_H_

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
enum class BoxCollider3DTag;

class ColliderObserver
{
public:
	virtual void OnNotified(BoxCollider3DTag other) = 0;
};

#endif