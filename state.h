#ifndef STATE_H
#define STATE_H


class Enemy;

class State
{
public:

	virtual ~State() {}

	
	virtual void Enter(Enemy*) = 0;

	
	virtual void Execute(Enemy*) = 0;


	virtual void Exit(Enemy*) = 0;

};

#endif