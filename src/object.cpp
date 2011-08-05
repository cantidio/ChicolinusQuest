#include "object.hpp"
#include "lua.hpp"
#include "sprite_manager.hpp"
#include "animation_manager.hpp"
#include "bg.hpp"

using namespace Gorgon::Script;
Object::Object(const Point& pPosition, const std::string& pScript, BG* pBG)
{
	Lua lua(pScript);
	lua.executeString("function _getXMaxAcceleration()	return max_acceleration[1] end"		);
	lua.executeString("function _getYMaxAcceleration()	return max_acceleration[2] end"		);
	lua.executeString("function _getXMoveAcceleration()	return move_acceleration[1] end"	);
	lua.executeString("function _getYMoveAcceleration()	return move_acceleration[2] end"	);
	lua.executeString("function _getXOffset()			return offset[1]	end"			);
	lua.executeString("function _getYOffset()			return offset[2] 	end"			);
	//sprite helper functions
	lua.executeString("function _getSpritesFile()		return sprites.file		or \"\"	end"	);
	lua.executeString("function _getSpritesWidth()		return sprites.width	or 0	end"	);
	lua.executeString("function _getSpritesHeight()		return sprites.height	or 0	end"	);
	lua.executeString("function _getSpritesAlphaR()		return sprites.alpha.r	or 0 	end"	);
	lua.executeString("function _getSpritesAlphaG()		return sprites.alpha.g	or 0 	end"	);
	lua.executeString("function _getSpritesAlphaB()		return sprites.alpha.b	or 0 	end"	);
	lua.executeString("function _getCollisionValue(i)	return collision[i + 1]	or 0 	end"	);

	//-sprite helper functions

	mSpritesName		= lua.function("_getSpritesFile", LuaParam(""), 1).getStringValue();
	mAnimationName		= lua.getStringVar("animation");
	mPosition			= pPosition;
	mDirection			= lua.getNumericVar("direction");
	mName				= lua.getStringVar("name");
	mCurrentAcceleration= Point(0,0);
	mFriction			= Point( 0.3, 0.3 );
	mMaxAcceleration.x	= lua.function("_getXMaxAcceleration"	, LuaParam(""), 1).getNumericValue();
	mMaxAcceleration.y	= lua.function("_getYMaxAcceleration"	, LuaParam(""), 1).getNumericValue();
	mMoveAcceleration.x	= lua.function("_getXMoveAcceleration"	, LuaParam(""), 1).getNumericValue();
	mMoveAcceleration.y	= lua.function("_getYMoveAcceleration"	, LuaParam(""), 1).getNumericValue();
	mOffset.x			= lua.function("_getXOffset"			, LuaParam(""), 1).getNumericValue();
	mOffset.y			= lua.function("_getYOffset"			, LuaParam(""), 1).getNumericValue();
	mCollision.a.x		= lua.function("_getCollisionValue"		, LuaParam("i", 0), 1).getNumericValue();
	mCollision.a.y		= lua.function("_getCollisionValue"		, LuaParam("i", 1), 1).getNumericValue();
	mCollision.b.x		= lua.function("_getCollisionValue"		, LuaParam("i", 2), 1).getNumericValue();
	mCollision.b.y		= lua.function("_getCollisionValue"		, LuaParam("i", 3), 1).getNumericValue();

	mSprites = SpriteManager::load
	(
		mSpritesName,
		lua.function("_getSpritesWidth",	LuaParam(""), 1).getNumericValue(),
		lua.function("_getSpritesHeight",	LuaParam(""), 1).getNumericValue(),
		al_map_rgb
		(
			lua.function("_getSpritesAlphaR", LuaParam(""), 1).getNumericValue(),
			lua.function("_getSpritesAlphaG", LuaParam(""), 1).getNumericValue(),
			lua.function("_getSpritesAlphaB", LuaParam(""), 1).getNumericValue()
		)
	);

	mAnimation			= AnimationManager::load( mAnimationName );
	mAnimationIsOver	= false;
	mNeedToDestroy		= false;
	mTimeOn				= 0;
	mFrameOn			= 0;
	mAnimationOn		= 0;
	mBG					= pBG;
}

Object::~Object()
{
	printf("Object::~Object()\n");
	SpriteManager::unload		( mSpritesName );
	AnimationManager::unload	( mAnimationName );
	printf("end - Object::~Object()\n");
}

bool Object::needToDestroy() const
{
		return mNeedToDestroy;
}

bool Object::colide(const Object& pObject)
{
	return mCollision.colide( pObject.mCollision, mPosition, pObject.mPosition );
}

void Object::draw(const Point& pPosition)
{
	Point position;
	ALLEGRO_BITMAP* sprite = (*mSprites)[ mAnimation[mAnimationOn].mFrames[mFrameOn] ];

	position.x = mPosition.x + pPosition.x - (( mDirection == 0 ) ? mOffset.x : (al_get_bitmap_width(sprite) - mOffset.x) );
	position.y = mPosition.y + pPosition.y - mOffset.y;

	al_draw_bitmap
	(
		sprite,
		position.x,
		position.y,
		mDirection
	);
}

void Object::logic()
{
	mAnimationIsOver = false;
	mPosition.x += mCurrentAcceleration.x;
	mPosition.y += mCurrentAcceleration.y;

	++mTimeOn;
	if( mTimeOn >= mAnimation[mAnimationOn].delay )
	{
		mTimeOn = 0;
		++mFrameOn;
		if( mFrameOn >= mAnimation[mAnimationOn].mFrames.size() )
		{
			mFrameOn			= 0;
			mAnimationIsOver	= true;
		}
	}

	if(mCurrentAcceleration.x > 0 )
	{
		mCurrentAcceleration.x -= mFriction.x;
		if( mCurrentAcceleration.x < 0 )
		{
			mCurrentAcceleration.x = 0;
		}
	}
	else if(mCurrentAcceleration.x < 0 )
	{
		mCurrentAcceleration.x += mFriction.x;
		if( mCurrentAcceleration.x > 0 )
		{
			mCurrentAcceleration.x = 0;
		}
	}

	if(mCurrentAcceleration.y > 0 )
	{
		mCurrentAcceleration.y -= mFriction.y;
		if( mCurrentAcceleration.y < 0 )
		{
			mCurrentAcceleration.y = 0;
		}
	}
	else if(mCurrentAcceleration.y < 0 )
	{
		mCurrentAcceleration.y += mFriction.y;
		if( mCurrentAcceleration.y > 0 )
		{
			mCurrentAcceleration.y = 0;
		}
	}
}

bool Object::animationIsOver() const
{
	return mAnimationIsOver;
}

void Object::changeAnimation(const unsigned int& pAnimation, const bool pForce)
{
	if(pAnimation != mAnimationOn || pForce)
	{
		mAnimationOn	= pAnimation;
		mFrameOn		= 0;
		mTimeOn			= 0;
	}
}

void Object::operator = (const Object& pObject)
{
	mPosition			= pObject.mPosition;
	mDirection			= pObject.mDirection;
	mName				= pObject.mName;
	mMaxAcceleration	= pObject.mMaxAcceleration;
	mMoveAcceleration	= pObject.mMoveAcceleration;

	mSprites			= SpriteManager::load( mSpritesName, 0, 0, al_map_rgb(0,0,0) );
	mAnimation			= AnimationManager::load( mAnimationName );
	mAnimationIsOver	= false;
	mTimeOn				= 0;
	mFrameOn			= 0;
	mAnimationOn		= 0;
}
