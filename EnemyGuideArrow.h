//=====================================
//
//�G�l�~�[�K�C�h�A���[�w�b�_[EnemyGuideArrow.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _ENEMYGUIDEARROW_H_
#define _ENEMYGUIDEARROW_H_

#include "main.h"
#include "Framework\BaseParticle.h"
#include "Framework\BaseEmitter.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class EnemyGuideArrow : public BaseParticle
{
public:
	void Init();
	void Update();
};

class EnemyGuideArrowEmitter : public BaseEmitter
{
public:
	void Init();
	void Update();

	D3DXVECTOR3 start, end;
};

#endif