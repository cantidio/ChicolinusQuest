#include "bg.hpp"
using namespace Gorgon::Script;

BG::BG(const std::string& pScript)
{
	Lua lua(pScript);
	//register some help functions
	lua.executeString("function _getLayerNumber()		return #layers end");
	lua.executeString("function _getLayerImage(i)		return layers[i + 1].img end");
	lua.executeString("function _getLayerVelocityX(i)	return layers[i + 1].vel.x end");
	lua.executeString("function _getLayerVelocityY(i)	return layers[i + 1].vel.y end");
	lua.executeString("function _getPlayerXPosition()	return playerPosition[1] end");
	lua.executeString("function _getPlayerYPosition()	return playerPosition[2] end");

	mName				= lua.getNumericVar("BG_name");
	mWidth				= lua.getNumericVar("BG_width");
	mHeight				= lua.getNumericVar("BG_height");
	mPosition.x			= lua.function("_getXPosition"		, LuaParam(""), 1).getNumericValue();
	mPosition.y			= lua.function("_getYPosition"		, LuaParam(""), 1).getNumericValue();

	Point playerPosition;
	mPlayerLayer		= lua.getNumericVar("playerLayer");
	playerPosition.x	= lua.function("_getPlayerXPosition", LuaParam(""), 1).getNumericValue();
	playerPosition.y	= lua.function("_getPlayerYPosition", LuaParam(""), 1).getNumericValue();
	const int layerNum	= lua.function("_getLayerNumber"	, LuaParam(""), 1).getNumericValue();

	for(register int i = 0 ; i < layerNum; ++i)
	{
		mLayers.push_back
		(
			new BGLayer
			(
				lua.function("_getLayerImage", LuaParam("i",i), 1).getStringValue(),
				Point
				(
					lua.function("_getLayerVelocityX", LuaParam("i",i), 1).getNumericValue(),
					lua.function("_getLayerVelocityY", LuaParam("i",i), 1).getNumericValue()
				)
			)
		);

		if(i == mPlayerLayer)
		{
//			mLayer[i]->addObject( PLAYER );
		}
	}
}

BG::~BG()
{
	for(unsigned int i = 0 ; i < mLayers.size(); ++i)
	{
		delete mLayers[i];
	}
	mLayers.clear();
}

void BG::draw() const
{
	for(unsigned int i = 0 ; i < mLayers.size(); ++i)
	{
		mLayers[i]->draw(mPosition);;
	}
}

void BG::logic()
{
	for(unsigned int i = 0 ; i < mLayers.size(); ++i)
	{
		mLayers[i]->logic();
	}
}

BGLayer* BG::getLayer(const unsigned int& pLayer)
{
	return mLayers[pLayer];
}
