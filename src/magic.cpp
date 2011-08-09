#include "magic.hpp"
#include "game.hpp"
Magic::Magic(const Point& pPosition, const int& pDir, const Magic::Type& pType, BG* pBG) :
	Object( pPosition, "data/obj/effects/magic.lua", pBG )
{
	mType		= pType;
	mActive		= true;
	mDirection	= pDir;
	mState		= &Magic::stateCreateInit;
	mSCreate	= audiere::OpenSoundEffect( Game::getAudioDevice(), "data/obj/effects/efeito3.wav"			, audiere::MULTIPLE );
	mSDestroy	= audiere::OpenSoundEffect( Game::getAudioDevice(), "data/obj/effects/efeito1.wav"			, audiere::MULTIPLE );
	mDuration	= 60;
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

void Magic::destroy()
{
	if( mActive )
	{
		printf("tchau1\n");
		mState	= &Magic::stateDestroyInit;
		mActive	= false;
	}
}

void Magic::stateCreateInit()
{
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
	mSCreate->play();
	mState =  &Magic::stateCreating;
}

void Magic::stateCreating()
{
	if( animationIsOver() )
	{
		mState =  &Magic::stateStandInit;
	}
}

void Magic::stateStandInit()
{
	switch( mType )
	{
		case Magic::ICE:	changeAnimation( 1 );	break;
		case Magic::FIRE:	changeAnimation( 4 );	break;
		case Magic::ROCK:	changeAnimation( 7 );	break;
	}
	mState =  &Magic::stateStanding;
}

void Magic::stateStanding()
{
	mCurrentAcceleration.x = (mDirection) ? 5 : -5;
	--mDuration;
	if(mDuration <= 0)
	{
		destroy();
	}
}

void Magic::stateDestroyInit()
{
	switch( mType )
	{
		case Magic::ICE:	changeAnimation( 3 );	break;
		case Magic::FIRE:	changeAnimation( 6 );	break;
		case Magic::ROCK:	changeAnimation( 8 );	break;
	}
	mSDestroy->play();
	mState =  &Magic::stateDestroing;
	mCurrentAcceleration.x = 0;
	mCurrentAcceleration.y = 0;
}

void Magic::stateDestroing()
{
	if( animationIsOver() )
	{
		mNeedToDestroy = true;
	}
}
