#include "bg_layer.hpp"
#include "lua.hpp"

int BGLayer::mTileSize = 16;
using namespace Gorgon::Script;
BGLayer::BGLayer(const std::string& pScript)
{
	Lua lua(pScript);
	lua.executeString("function __getTile(i,j)	return map[i + 1][j + 1] end");
	lua.executeString("function __getVTiles()	return #map end");
	lua.executeString("function __getHTiles()	if map then return #map[1] end	return 0 end");

	mWidth					= lua.getNumericVar("width");
	mHeight					= lua.getNumericVar("height");
	mScrollingVelocity.x	= lua.getNumericVar("scrollX");
	mScrollingVelocity.y	= lua.getNumericVar("scrollY");

	mHTiles = lua.function("__getHTiles", LuaParam(), 1).getNumericValue();
	mVTiles = lua.function("__getVTiles", LuaParam(), 1).getNumericValue();

	//mTileMap				= (int**) calloc( mVTiles, sizeof(int*) );
	mTileMap				= new int*[mVTiles];

	for(register int i = 0; i < mVTiles ; ++i)
	{
//		mTileMap[i] = (int*)calloc( mHTiles, sizeof(int) );
		mTileMap[i] = new int[mHTiles];
		for(register int j = 0; j < mHTiles; ++j)
		{
			mTileMap[i][j] = lua.function("__getTile", LuaParam("ii",i,j), 1).getNumericValue();
		}
	}
}

BGLayer::~BGLayer()
{
	for(register int i = 0; i < mVTiles ; ++i)
	{
		//free( mTileMap[i] );
		delete mTileMap[i];
	}
	//free( mTileMap );
	delete mTileMap;

	for(register unsigned int i = 0; i < mObjects.size(); ++i)
	{
		delete mObjects[i];
	}
	mObjects.clear();
}

void BGLayer::addObject(Object* pObject)
{
	mObjects.push_back(pObject);
}

void BGLayer::draw(const Point& pPosition) const
{
	const int width		= 320; //pegar os dados do ecrã
	const int height	= 240;

	//draw layer
	const double base_x = pPosition.x * mScrollingVelocity.x;	
	const double base_y = pPosition.y * mScrollingVelocity.y;
	const int x_beg		= (int)(base_x / mHTiles);
	const int y_beg		= (int)(base_y / mVTiles);	
	const int x_end		= x_beg + ( width	/ mHTiles );
	const int y_end		= y_beg + ( height	/ mVTiles );

	for(register int i = y_beg; i < mHeight && i < y_end; ++i)
	{
		const int dest_y = base_y + (i * mTileSize);
		for(register int j = x_beg; j < mWidth && j < x_end; ++j)
		{
			const int dest_x = base_x + j * mTileSize;
			al_draw_bitmap_region
			(
				mTileSheet,
				mTileMap[i][j] * mHTiles,
				0,
				mHTiles,
				mVTiles,
				dest_x,
				dest_y,
				0
			);
		}
	}
	//draw objects
	for(register unsigned int i = 0; i < mObjects.size(); ++i)
	{
		mObjects[i]->draw( Point( base_x, base_y ) );
	}
}

void BGLayer::logic()
{
	for(register unsigned int i = 0; i < mObjects.size(); ++i)
	{
		mObjects[i]->logic();
	}
}
