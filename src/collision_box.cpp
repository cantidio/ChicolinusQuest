#include "collision_box.hpp"
Collision::Collision(){}
Collision::Collision( const Point& pA, const Point& pB )
{
	a = pA;
	b = pB;
}

bool Collision::colide( const Collision& pCollision, const Point& pPosA, const Point& pPosB ) const
{
    if
	(!(
		( pPosA.x + a.x > pPosB.x + pCollision.b.x )	||
		( pPosA.y + a.y > pPosB.y + pCollision.b.y )	||
		( pPosA.x + b.x < pPosB.x + pCollision.a.x )	||
		( pPosA.y + b.y < pPosB.y + pCollision.a.y )
	))
	{
		return true;
	}
	return false;
}
