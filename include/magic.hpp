#ifndef _MAGIC_
#define _MAGIC_
#include "object.hpp"

class Magic : public Object
{
	public:
		enum Type /**< Enum with the magic types*/
		{
			FIRE,
			ICE,
			ROCK,
			MAGIC_NUMBER
		};
		Magic(const Point& pPosition, const int& pDir, const Magic::Type& pType, BG* pBG);
		virtual void logic();

		int getDamage() const;
		bool isActive() const;
		void destroy();
	protected:
		audiere::SoundEffectPtr	mSCreate;
		audiere::SoundEffectPtr	mSDestroy;
		bool	mActive;
		int		mDamage;
		float	mDuration;
		Type	mType;
		void (Magic::*mState)();  /**<< pointer to the magic state*/

		void stateCreateInit();
		void stateCreating();
		void stateStandInit();
		void stateStanding();
		void stateDestroyInit();
		void stateDestroing();
};
#endif
