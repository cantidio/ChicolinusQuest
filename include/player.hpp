#ifndef _PLAYER_
#define _PLAYER_
#include "object.hpp"

class Player : public Object
{
    protected:
		int mLevel;
		int mLevelMax;
		int mLife;
		int mLifeMax;
		int mHunger;
		int mHungerMax;
		bool mCanShot;
		void (Player::*mState)();  /**<< pointer to the player state*/
    public:
		Player(const Point& pPosition);
		~Player();
		bool move();
		bool isDead() const;
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
};
#endif

/*
Personagem é ummagico zumbi, que foi transformado em zumbi por um padrinho mágico do mal
para voltar a ser quem ele era antes, ele precisa matar o mago e beber o sangue dele.
Para matar o mago, o zumbi mago, deverá conseguir novas varinhas e poderes mágicos.
Como ele é um zumbi, ele deve se alimentar dos inimigos das fases para não morrer...
Terá uma barra de fome para isso, que ficará diminuindo conforme o tempo...
terá life tbm.
*/
