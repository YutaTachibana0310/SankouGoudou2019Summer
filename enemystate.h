#ifndef ENEMY_STATE_H
#define ENEMY_STATE_H

#include "State.h"


class Enemy;

//stateÇèëÇ≠
class Straight : public State
{
private:

	Straight() {}

	
	Straight(const Straight&);
	//Straight& operator=(const EStraight&);

public:

	
	static Straight* Instance();

	virtual void Enter(Enemy* pEnemy);

	virtual void Execute(Enemy* pEnemy);

	virtual void Exit(Enemy* pEnemy);
};



class Flat : public State
{
private:

	Flat() {}


	Flat(const Flat&);
	//Flat& operator=(const Flat&);

public:


	static Flat* Instance();

	virtual void Enter(Enemy* pEnemy);

	virtual void Execute(Enemy* pEnemy);

	virtual void Exit(Enemy* pEnemy);
};




#endif
