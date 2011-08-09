#ifndef _ENEMY_WIZARD_
#define _ENEMY_WIZARD_
#include "enemy.hpp"

class EnemyWizard : public Enemy
{
	public:
		EnemyWizard(const Point& pPosition, BG* pBG);
		virtual void logic();

		virtual void hurt(const float& pDamage);
	protected:
		audiere::SoundEffectPtr	mSShot;
		audiere::SoundEffectPtr	mSHurt;
		audiere::SoundEffectPtr	mSDie;

		void (EnemyWizard::*mState)();  /**<< pointer to the magic state*/
		void stateStandInit();
		void stateStanding();
		void stateHurtInit();
		void stateHurting();
};
#endif
