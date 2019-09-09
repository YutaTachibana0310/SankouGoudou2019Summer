//=====================================
//
// PlayerFalldown.h
// �@�\:�v���C���[�̒ė�����
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _PLAYERFALLDOWN_H_
#define _PLAYERFALLDOWN_H_

#include "main.h"
#include "IStateMachine.h"
#include "Player.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class PlayerFalldown : public IStateMachine<Player>
{
public:
	void OnStart(Player* entity);
	int OnUpdate(Player* entity);

private:
	D3DXVECTOR3 initPos;

}; 
#endif