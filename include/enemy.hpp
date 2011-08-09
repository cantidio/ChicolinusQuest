#ifndef _ENEMY_
#define _ENEMY_
#include "actor.hpp"

class Enemy : public Actor
{
	public:
		Enemy( const Point& pPosition, const std::string& pScript, BG* pBG );
		virtual void logic() = 0;
		virtual void hurt(const float& pDamage) = 0;
};
#endif
