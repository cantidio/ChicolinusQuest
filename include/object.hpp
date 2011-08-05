#ifndef _OBJECT_
#define _OBJECT_
#include "point.hpp"
#include "spritepack.hpp"
#include "animationpack.hpp"
#include "include.hpp"
#include "collision_box.hpp"
class BG;
class Object
{
	protected:
		Point			mPosition;
		Point			mMaxAcceleration;
		Point			mMoveAcceleration;
		Point			mCurrentAcceleration;
		Point			mOffset;
		Point			mFriction;
		Collision		mCollision;
		BG*				mBG;

		int				mDirection;
		std::string		mName;
		std::string		mSpritesName;
		std::string		mAnimationName;
		SpritePack		*mSprites;
		AnimationPack	mAnimation;
		unsigned int	mTimeOn;
		unsigned int 	mAnimationOn;
		unsigned int	mFrameOn;
		bool			mAnimationIsOver;
		bool			mNeedToDestroy;


	public:
		Object(const Point& pPosition, const std::string& pScript, BG* pBG);
		Object(const Object& pObject);
		~Object();
		bool colide(const Object& pObject);
		void draw(const Point& pPosition);
		virtual void logic();
		bool needToDestroy() const;
		bool animationIsOver() const;
		void changeAnimation( const unsigned int& pAnimation, const bool pForce = false );
		void operator = (const Object& pObject);
};
#endif
