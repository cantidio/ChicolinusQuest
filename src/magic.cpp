#include "magic.hpp"

Magic::Magic(const Point& pPosition, const int& pDir, const Magic::Type& pType, BG* pBG) :
	Object( pPosition, "data/obj/effects/magic.lua", pBG )
{
	mType		= pType;
	mActive		= true;
	mDirection	= pDir;
	mState		= &Magic::stateCreate;

	switch( mType )
	{
		case Magic::FIRE:
			mDamage = 3 ;
			changeAnimation( 3 );
			break;
		case Magic::ICE:
			mDamage = 4 ;
			changeAnimation( 0 );
			break;
		case Magic::ROCK:
			mDamage	= 1 ;
			changeAnimation( 6 );
			break;
	}
}

void Magic::logic()
{
	Object::logic();
	((this)->*mState) () ;
}

int Magic::getDamage() const
{
	return mDamage;
}

bool Magic::isActive() const
{
	return mActive;
}

void Magic::stateCreate()
{
	if( animationIsOver() )
	{
		mState =  &Magic::stateStand;
		switch( mType )
		{
			case Magic::ICE:	changeAnimation( 1 );	break;
			case Magic::FIRE:	changeAnimation( 4 );	break;
			case Magic::ROCK:	changeAnimation( 7 );	break;
		}
	}
}

void Magic::stateStand()
{
	mCurrentAcceleration.x = (mDirection) ? 5 : -5;
	/*
	switch( mType )
	{
		case Magic::FIRE:	mCurrentAcceleration.x = (mDirection) ? 5 : -5;		break;
		case Magic::ICE:	mCurrentAcceleration.x = (mDirection) ? 5 : -5;		break;
		case Magic::ROCK:	mCurrentAcceleration.x = (mDirection) ? 5 : -5;		break;
	}*/
}

void Magic::stateDestroy()
{
	if( animationIsOver() )
	{
		mNeedToDestroy = true;
	}
}

