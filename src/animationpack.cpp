#include "animationpack.hpp"
#include "lua.hpp"
using namespace Gorgon::Script;
static Animation notFound;

AnimationPack::AnimationPack()
{

}

AnimationPack::AnimationPack(const std::string& pScript)
{
	Lua lua(pScript);
	//animationpack helper functions
	lua.executeString("function _getAnimationNumber()			return #animations						or 0	end");
	lua.executeString("function _getAnimationDelay(i)			return animations[i + 1].delay			or 1	end");
	lua.executeString("function _getAnimationFrameNumber(i)		return #animations[i + 1].frames		or 0	end");
	lua.executeString("function _getAnimationFrame(i,j)			return animations[i + 1].frames[j + 1]	or 0	end");
	//-animationpack helper functions

	const int animationNumber = lua.function("_getAnimationNumber", LuaParam(), 1).getNumericValue();
	for(int i = 0; i < animationNumber; ++i)
	{
		Animation aux;
		aux.delay				= lua.function("_getAnimationDelay"			, LuaParam("i",i), 1).getNumericValue();
		const int frameNumber	= lua.function("_getAnimationFrameNumber"	, LuaParam("i",i), 1).getNumericValue();

		for(int j = 0; j < frameNumber; ++j)
		{
			aux.mFrames.push_back( lua.function("_getAnimationFrame", LuaParam("ii",i,j), 1).getNumericValue() - 1 );
		}
		mAnimation.push_back( aux );
	}
}

int AnimationPack::size() const
{
	return mAnimation.size();
}

Animation& AnimationPack::operator[](const unsigned int& pIndex)
{
	if( pIndex < mAnimation.size() )
	{
		return mAnimation[pIndex];
	}

	return notFound;
}

