#include "enemy_wizard.hpp"
#include "game.hpp"

EnemyWizard::EnemyWizard( const Point& pPosition, BG* pBG ) : Enemy( pPosition, "data/obj/enemy/wizard/wizard.lua", pBG )
{
	mState	=  &EnemyWizard::stateStandInit;
	mSShot	= audiere::OpenSoundEffect( Game::getAudioDevice(), "data/obj/enemy/wizard/golpe1.wav"			, audiere::MULTIPLE );
	mSHurt	= audiere::OpenSoundEffect( Game::getAudioDevice(), "data/obj/enemy/wizard/hurt.wav"			, audiere::MULTIPLE );
	mSDie	= audiere::OpenSoundEffect( Game::getAudioDevice(), "data/obj/enemy/wizard/morrendo.wav"		, audiere::MULTIPLE );

	mSHurt->setVolume(0.5);
}

void EnemyWizard::logic()
{
	Object::logic();
	((this)->*mState) () ;
}

void EnemyWizard::hurt( const float& pDamage )
{
	mLife -= pDamage;
	mState =  &EnemyWizard::stateHurtInit;
}

void EnemyWizard::stateStandInit()
{
	changeAnimation( 0 );
	mState =  &EnemyWizard::stateStanding;
}

void EnemyWizard::stateStanding()
{

}

void EnemyWizard::stateHurtInit()
{
	changeAnimation( 3 );
	mSHurt->play();
	mState =  &EnemyWizard::stateHurting;
}

void EnemyWizard::stateHurting()
{
	if( animationIsOver() )
	{
		mState =  &EnemyWizard::stateStandInit;
	}
}
