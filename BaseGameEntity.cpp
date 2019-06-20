#include "BaseGameEntity.h"
#include <cassert>

int BaseGameEntity::m_iNextValidID = 0;

void BaseGameEntity::SetID(int val)
{
	
	assert((val >= m_iNextValidID) && "<BaseGameEntity::SetID>: invalid ID");

	m_ID = val;

	m_iNextValidID = m_ID + 1;
}
