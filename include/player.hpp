#ifndef _PLAYER_
#define _PLAYER_
#include "actor.hpp"

class Player : public Actor
{
    protected:
		audiere::SoundEffectPtr	mSFire;
		audiere::SoundEffectPtr	mSSpecial;
		audiere::SoundEffectPtr	mSHurt;
		audiere::SoundEffectPtr	mSDying;
		audiere::SoundEffectPtr	mSJumping;
		audiere::SoundEffectPtr	mSSteps;
		audiere::SoundEffectPtr	mSLand;

		int mLevel;
		int mLevelMax;

		float mHunger;
		float mHungerMax;
		bool mCanShot;
		void (Player::*mState)();  /**<< pointer to the player state*/
    public:
		Player(const Point& pPosition, BG* pBG);
		~Player();
		bool move();

		virtual void logic();
		//---------------------------STATES--------------------------------
		void stateStandInit();			void stateStanding();
		void stateWalkInit();			void stateWalking();
		void stateShotInit();			void stateShotting();
		void stateSpecialShotInit();	void stateSpecialShotting();
		void stateJumpInit();			void stateJumping();
		void stateFallInit();			void stateFalling();
		void stateHurtStandInit();		void stateHurtingStand();
		void stateHurtInAirInit();		void stateHurtingInAir();
		void stateDieInit();			void stateDying();
		//---------------------------STATES--------------------------------

		void hurt(const float& pDamage);
};
#endif

/*
Personagem � ummagico zumbi, que foi transformado em zumbi por um padrinho m�gico do mal
para voltar a ser quem ele era antes, ele precisa matar o mago e beber o sangue dele.
Para matar o mago, o zumbi mago, dever� conseguir novas varinhas e poderes m�gicos.
Como ele � um zumbi, ele deve se alimentar dos inimigos das fases para n�o morrer...
Ter� uma barra de fome para isso, que ficar� diminuindo conforme o tempo...
ter� life tbm.
*/
