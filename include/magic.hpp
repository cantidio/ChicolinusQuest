#ifndef _MAGIC_
#define _MAGIC_
#include "object.hpp"

class Magic : public Object
{
	public:
		enum Type
		{
			FIRE,
			ICE,
			ROCK,
			MAGIC_NUMBER
		};
		Magic(const Point& pPosition, const int& pDir, const Magic::Type& pType, BG* pBG);
		void stateCreate();
		void stateStand();
		void stateDestroy();
		int getDamage() const;
		bool isActive() const;

		virtual void logic();
	protected:
		bool mActive;
		int mDamage;
		Type mType;
		void (Magic::*mState)();  /**<< pointer to the player state*/
};
#endif
