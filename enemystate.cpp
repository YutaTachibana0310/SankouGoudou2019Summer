#include "enemystate.h"


#include <iostream>
using std::cout;

//define this to output to a file
#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif





//method

Straight* Straight::Instance()
{
	static Straight instance;

	return &instance;
}

void Straight::Enter(Enemy* pEnemy)
{
	
}


void Straight::Execute(Enemy* pEnemy)
{
	
	

	
	//straight-->flat
	/*if (//)
	{
		pEnemy->ChangeState(Flat::Instance());
	}*/
}


void Straight::Exit(Enemy* pEnemy)
{
	
}






Flat* Flat::Instance()
{
	static Flat instance;

	return &instance;
}

void Flat::Enter(Enemy* pEnemy)
{

}


void Flat::Execute(Enemy* pEnemy)
{





	
}


void Flat::Exit(Enemy* pEnemy)
{

}



