#include "bg.hpp"
using namespace Gorgon::Script;

BG::BG(std::string& pScript)
{
	Lua lua(pScript);
	//register some help functions
	lua.executeString("function _getLayerNumber()		return #layers end");
	lua.executeString("function _getLayer(i)			return layers[i + 1] end");
	lua.executeString("function _getXPosition()			return BG_initialPosition[1] end");
	lua.executeString("function _getYPosition()			return BG_initialPosition[2] end");
	lua.executeString("function _getX1GoalRectangle()	return BG_goalRectangle[1] end");
	lua.executeString("function _getY1GoalRectangle()	return BG_goalRectangle[2] end");
	lua.executeString("function _getX2GoalRectangle()	return BG_goalRectangle[3] end");
	lua.executeString("function _getY2GoalRectangle()	return BG_goalRectangle[4] end");
	lua.executeString("function _getPlayerXPosition()	return playerPosition[1] end");
	lua.executeString("function _getPlayerYPosition()	return playerPosition[2] end");

	mName				= lua.getNumericVar("BG_name");
	mWidth				= lua.getNumericVar("BG_width");
	mHeight				= lua.getNumericVar("BG_height");
	mPosition.x			= lua.function("_getXPosition"		, LuaParam(""), 1).getNumericValue();
	mPosition.y			= lua.function("_getYPosition"		, LuaParam(""), 1).getNumericValue();
	mCollisionBox.a.x	= lua.function("_getX1GoalRectangle", LuaParam(""), 1).getNumericValue();
	mCollisionBox.a.y	= lua.function("_getY1GoalRectangle", LuaParam(""), 1).getNumericValue();
	mCollisionBox.b.x	= lua.function("_getX2GoalRectangle", LuaParam(""), 1).getNumericValue();
	mCollisionBox.b.y	= lua.function("_getY2GoalRectangle", LuaParam(""), 1).getNumericValue();

	Point playerPosition;
	mPlayerLayer		= lua.getNumericVar("playerLayer");
	playerPosition.x	= lua.function("_getPlayerXPosition", LuaParam(""), 1).getNumericValue();
	playerPosition.y	= lua.function("_getPlayerYPosition", LuaParam(""), 1).getNumericValue();
	const int layerNum	= lua.function("_getLayerNumber"	, LuaParam(""), 1).getNumericValue();

	for(register int i = 0 ; i < layerNum; ++i)
	{
		mLayers.push_back(new BGLayer(   lua.function("_getLayer", LuaParam(""), 1).getStringValue()  ));

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

}

void BG::logic()
{

}

