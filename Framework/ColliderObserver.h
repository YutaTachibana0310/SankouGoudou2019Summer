//=====================================
//
//�R���C�_�[�I�u�U�[�o�[�w�b�_[ColliderObserver.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _COLLIDEROBSERVER_H_
#define _COLLIDEROBSERVER_H_

#include "BoxCollider3D.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class ColliderObserver
{
public:
	virtual void OnNotify(BoxCollider3DTag other) = 0;
};

#endif