#ifndef _COLLISION_BOX_
#define _COLLISION_BOX_
#include "point.hpp"
#include "include.hpp"

class Collision
{
	public:
		Point a;
		Point b;
		Collision( const Point& pA, const Point& pB );
		Collision();
		bool colide( const Collision& pCollisionBox, const Point& pPosA, const Point& pPosB ) const;
};
#endif
