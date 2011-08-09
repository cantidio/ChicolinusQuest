#ifndef _ACTOR_
#define _ACTOR_
#include "object.hpp"

class Actor : public Object
{
	protected:
		float mLife;		/**<< actual life of the actor*/
		float mLifeMax;		/**<< the max amount of life the actor can have*/
	public:
		Actor
		(
			const Point&		pPosition,
			const std::string&	pScript,
			BG*					pBG
		);

		inline bool isDead() const
		{
			return (mLife <= 0 );
		}

		inline int getLife() const
		{
			return mLife;
		}

		inline float getLifeMax() const
		{
			return mLifeMax;
		}

		inline void subLife(const float& pLife)
		{
			mLife -= pLife;
			if( mLife < 0)
			{
				mLife = 0;
			}
		}

		inline void addLife(const float& pLife)
		{
			mLife += pLife;
			if( mLife > mLifeMax )
			{
				mLife = mLifeMax;
			}
		}
};
#endif
