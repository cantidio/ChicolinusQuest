#ifndef _ANIMATION_PACK_
#define _ANIMATION_PACK_

#include "include.hpp"

typedef struct
{
	std::vector<int> mFrames;
	unsigned int delay;
}Animation;

class AnimationPack
{
	protected:
		std::vector<Animation> mAnimation;
	public:
		AnimationPack();
		AnimationPack(const std::string& pScript);
		Animation& operator[](const unsigned int& pIndex);
		int size() const;
};
#endif
