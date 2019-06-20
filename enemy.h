#ifndef MINER_H
#define MINER_H

#include <string>
#include <cassert>

#include "BaseGameEntity.h"



class State;


class Enemy : public BaseGameEntity
{
private:

	State*                m_pCurrentState;


	//エネミーの属性

public:

	Enemy(int id);

	
	void Update();

	void Draw();

	void Uninit();
	void ChangeState(State* new_state);



};




#endif
