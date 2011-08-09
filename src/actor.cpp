#include "actor.hpp"
#include "lua.hpp"
using namespace Gorgon::Script;

Actor::Actor( const Point& pPosition, const std::string& pScript, BG* pBG )
	: Object(pPosition, pScript, pBG)
{
	Lua lua( pScript );
	mLife		= lua.getNumericVar("life");
	mLifeMax	= lua.getNumericVar("lifeMax");
}
