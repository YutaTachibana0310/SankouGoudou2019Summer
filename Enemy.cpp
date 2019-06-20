#include "Enemy.h"
#include "enemystate.h"

Enemy::Enemy(int id) :BaseGameEntity(id)

{}


void Enemy::ChangeState(State* pNewState)
{
	
	assert(m_pCurrentState && pNewState);

	
	m_pCurrentState->Exit(this);

	
	m_pCurrentState = pNewState;

	
	m_pCurrentState->Enter(this);
}


void Enemy::Update()
{
	
	if (m_pCurrentState)
	{
		m_pCurrentState->Execute(this);
	}
}


