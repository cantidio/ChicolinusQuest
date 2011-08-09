#include "player.hpp"
#include "lua.hpp"
#include "input.hpp"
#include "magic.hpp"
#include "game.hpp"
#include "math.h"
#include "bg.hpp"

using namespace Gorgon::Script;

Player::Player(const Point& pPosition, BG* pBG) :
	Actor(pPosition, "data/obj/player/Chicus/chicus.lua", pBG)
{
	Lua lua("data/obj/player/Chicus/chicus.lua");
	mLevel 		= lua.getNumericVar("level");
	mLevelMax	= lua.getNumericVar("levelMax");
	mHunger		= lua.getNumericVar("hunger");
	mHungerMax	= lua.getNumericVar("hungerMax");

	mSSteps		= audiere::OpenSoundEffect( Game::getAudioDevice(), "data/obj/effects/passo1.wav"			, audiere::MULTIPLE );
	mSLand		= audiere::OpenSoundEffect( Game::getAudioDevice(), "data/obj/effects/efeito2.wav"			, audiere::MULTIPLE );
	mSMagic		= audiere::OpenSoundEffect( Game::getAudioDevice(), "data/obj/effects/efeito3.wav"			, audiere::MULTIPLE );
	mSFire		= audiere::OpenSoundEffect( Game::getAudioDevice(), "data/obj/player/chicus/atacando.wav"	, audiere::MULTIPLE );
	mSSpecial	= audiere::OpenSoundEffect( Game::getAudioDevice(), "data/obj/player/chicus/especial.wav"	, audiere::MULTIPLE );
	mSJumping	= audiere::OpenSoundEffect( Game::getAudioDevice(), "data/obj/player/chicus/pulando.wav"	, audiere::MULTIPLE );
	mSDying		= audiere::OpenSoundEffect( Game::getAudioDevice(), "data/obj/player/chicus/morrendo.wav"	, audiere::MULTIPLE );
	mSHurt		= audiere::OpenSoundEffect( Game::getAudioDevice(), "data/obj/player/chicus/dano.wav"		, audiere::MULTIPLE );

	mSLand->setVolume		( 0.3 );
	mSFire->setVolume		( 0.5 );
	mSSpecial->setVolume	( 0.5 );
	mSJumping->setVolume	( 0.5 );
	mSDying->setVolume		( 5.5 );
	mSHurt->setVolume		( 0.3 );
	mState = &Player::stateStandInit;
}

Player::~Player(){}

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
	else if( move() )
	{
		if( ( mFrameOn == 1 || mFrameOn == 5 ) && mTimeOn == 0 )
		{
			mSSteps->play();
		}
	}
	else
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
	mSFire->play();
}

void Player::stateShotting()
{
	if(mFrameOn == 3 && mCanShot)
	{

		mSMagic->play();
		mCanShot = false;
		printf("shot\n");
		if(mDirection == 0)
		{
            Game::addMagic( new Magic(Point( mPosition.x + 30, mPosition.y + 15 ) , 1, Magic::FIRE, mBG) );
		}
		else
		{
		    Game::addMagic( new Magic(Point( mPosition.x - 30, mPosition.y + 15 ) , 0, Magic::FIRE, mBG) );
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
	mSSpecial->play();
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
            	mSMagic->play();
                mCanShot = false;
                printf("shot\n");
                double y = sin(mFrameOn)* 5;
                int magic = rand()%Magic::MAGIC_NUMBER;
                if(mDirection == 0)
                {
                    Game::addMagic( new Magic(Point( mPosition.x + 30, mPosition.y + 15 + y ) , 1, (Magic::Type) magic, mBG) );
                }
                else
                {
                    Game::addMagic( new Magic(Point( mPosition.x - 30, mPosition.y + 15 + y ) , 0, (Magic::Type) magic, mBG) );
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

		mSJumping->play();
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
	else if( Input::get().button1() ) //shot
	{
		mState		= &Player::stateShotInit;
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
		mSLand->play();
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
	mSHurt->play();
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
	mSHurt->play();
}

void Player::stateHurtingInAir()
{
	if(animationIsOver())
	{
		printf("fal\n");
		mState = &Player::stateFallInit;
	}
}

void Player::stateDieInit()
{
	printf("player-state: die\n");
	changeAnimation( 9 );
	mState = &Player::stateDying;
	mSDying->play();
}

void Player::stateDying()
{
	if( animationIsOver() )
	{
		changeAnimation( 10 );
	}
}

void Player::hurt(const float& pDamage)
{
	mLife  -= pDamage;
	if
	(
		mState != &Player::stateHurtInAirInit
		&& mState != &Player::stateHurtingInAir
		&& mState != &Player::stateHurtStandInit
		&& mState != &Player::stateHurtingStand
	)
	{
		if
		(
			mState == &Player::stateFalling			||
			mState == &Player::stateFallInit		||
			mState == &Player::stateJumping			||
			mState == &Player::stateJumpInit		||
			mState == &Player::stateHurtInAirInit	||
			mState == &Player::stateHurtingInAir
		)
		{
			mState = &Player::stateHurtInAirInit;
		}
		else
		{
			mState = &Player::stateHurtStandInit;
		}
	}
}
