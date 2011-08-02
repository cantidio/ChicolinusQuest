#include "player.hpp"
#include "lua.hpp"
#include "input.hpp"
#include "magic.hpp"
#include "game.hpp"
#include "math.h"
using namespace Gorgon::Script;

Player::Player(const Point& pPosition) :
	Object(pPosition, "data/obj/player/Chicus/chicus.lua")
{
	Lua lua("data/obj/player/Chicus/chicus.lua");
	mLevel 		= lua.getNumericVar("level");
	mLevelMax	= lua.getNumericVar("levelMax");
	mLife		= lua.getNumericVar("life");
	mLifeMax	= lua.getNumericVar("lifeMax");
	mHunger		= lua.getNumericVar("hunger");
	mHungerMax	= lua.getNumericVar("hungerMax");

	mState = &Player::stateStandInit;
}

Player::~Player()
{
	printf("bye\n");
}

bool Player::isDead() const
{
	return (mLife <= 0 );
}

void Player::logic()
{
	Object::logic();
	((this)->*mState) () ;
}

bool Player::move()
{
	if( Input::get().buttonLeft() )
	{
		mCurrentAcceleration.x -= mMoveAcceleration.x;
		if( mCurrentAcceleration.x < -mMaxAcceleration.x)
		{
			mCurrentAcceleration.x = -mMaxAcceleration.x ;
		}
		mDirection = 1;
	}
	else if( Input::get().buttonRight() )
	{
		mCurrentAcceleration.x += mMoveAcceleration.x;
		if( mCurrentAcceleration.x > mMaxAcceleration.x)
		{
			mCurrentAcceleration.x = mMaxAcceleration.x ;
		}
		mDirection = 0;
	}
	else
	{
		return false;
	}
	return true;
}

void Player::stateStandInit()
{
	printf("player-state: stand\n");
	mState = & Player::stateStanding;
	changeAnimation( 0 );
}

void Player::stateStanding()
{
	if(isDead())
	{
		mState = &Player::stateDieInit;
	}
	else if( Input::get().button3() ) //special shot
	{
		mState = &Player::stateSpecialShotInit;
	}
	else if( Input::get().button1() ) //shot
	{
		mState = &Player::stateShotInit;
	}
	else if( Input::get().button2() ) //jump
	{
		mState = &Player::stateJumpInit;
	}
	else if( Input::get().buttonLeft() || Input::get().buttonRight() )
	{
		mState = &Player::stateWalkInit;
	}
}

void Player::stateWalkInit()
{
	printf("player-state: walk\n");
	changeAnimation( 1 );
	mState = &Player::stateWalking;
}

void Player::stateWalking()
{
	if(isDead())
	{
		mState = &Player::stateDieInit;
	}
	else if( Input::get().button3() ) //special shot
	{
		mState = &Player::stateSpecialShotInit;
	}
	else if( Input::get().button1() ) //shot
	{
		mState = &Player::stateShotInit;
	}
	else if( Input::get().button2() ) //jump
	{
		mState = &Player::stateJumpInit;
	}
	else if( !move() )
	{
		mState = &Player::stateStandInit;
	}
}

void Player::stateShotInit()
{
	printf("player-state: shot\n");
	changeAnimation( 2 );
	mState		= &Player::stateShotting;
	mCanShot	= true;
}

void Player::stateShotting()
{
	if(mFrameOn == 3 && mCanShot)
	{
		mCanShot = false;
		printf("shot\n");
		if(mDirection == 0)
		{
            Game::addMagic( new Magic(Point( mPosition.x + 30, mPosition.y + 15 ) , 1, Magic::FIRE) );
		}
		else
		{
		    Game::addMagic( new Magic(Point( mPosition.x - 30, mPosition.y + 15 ) , 0, Magic::FIRE) );
		}
	}
	if(isDead())
	{
		mState = &Player::stateDieInit;
	}
	else if(animationIsOver())
	{
		mState = &Player::stateStandInit;
	}
}

void Player::stateSpecialShotInit()
{
	printf("player-state: special shot\n");
	changeAnimation( 3 );
	mState = &Player::stateSpecialShotting;
}

void Player::stateSpecialShotting()
{
	if(isDead())
	{
		mState = &Player::stateDieInit;
	}
	else if(!animationIsOver())
	{
	    if( mFrameOn > 2 && mFrameOn%2 == 0 )
	    {
            if(mCanShot)
            {
                mCanShot = false;
                printf("shot\n");
                double y = sin(mFrameOn)* 5;
                if(mDirection == 0)
                {
                    Game::addMagic( new Magic(Point( mPosition.x + 30, mPosition.y + 15 + y ) , 1, Magic::FIRE) );
                }
                else
                {
                    Game::addMagic( new Magic(Point( mPosition.x - 30, mPosition.y + 15 + y ) , 0, Magic::FIRE) );
                }
            }
	    }
	    else
	    {
	        mCanShot = true;
	    }
	}
	else
	{
		mState = &Player::stateStandInit;
	}
}

void Player::stateJumpInit()
{
	changeAnimation( 4 );
	if( animationIsOver() )
	{
		printf("player-state: jump\n");
		mState = &Player::stateJumping;
		changeAnimation( 5 );
		mCurrentAcceleration.y = -7;
	}
}

void Player::stateJumping()
{
	move();
	if(isDead())
	{
		mState = &Player::stateDieInit;
	}
	else if( mCurrentAcceleration.y == 0 )
	{
		mState = &Player::stateFallInit;
	}
}

void Player::stateFallInit()
{
	printf("player-state: fall\n");
	changeAnimation( 6 );
	mState = &Player::stateFalling;
}

void Player::stateFalling()
{
	move();
	mCurrentAcceleration.y += mMoveAcceleration.y;
	if(isDead())
	{
		mState = &Player::stateDieInit;
	}
	else if( mCurrentAcceleration.y > mMaxAcceleration.y)
	{
		mCurrentAcceleration.y = mMaxAcceleration.y ;
	}
	if(mPosition.y >= 230)//to no chão manolo
	{
		mPosition.y = 230;
		mCurrentAcceleration.y = 0;
		mState = &Player::stateStandInit;
	}
}

void Player::stateHurtStandInit()
{
	printf("player-state: hurtStand\n");
	changeAnimation( 7 );
	mState = &Player::stateHurtingStand;
}

void Player::stateHurtingStand()
{
	if(animationIsOver())
	{
		mState = &Player::stateStandInit;
	}
}

void Player::stateHurtInAirInit()
{
	printf("player-state: hurtInAir\n");
	changeAnimation( 8 );
	mState = &Player::stateHurtingInAir;
}

void Player::stateHurtingInAir()
{
	if(animationIsOver())
	{
		mState = &Player::stateFallInit;
	}
}

void Player::stateDieInit()
{
	printf("player-state: die\n");
	changeAnimation( 9 );
}

void Player::stateDying()
{
	if(animationIsOver())
	{
		changeAnimation( 10 );
	}
}
