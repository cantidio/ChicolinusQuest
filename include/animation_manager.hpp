#ifndef _ANIMATION_MANAGER_
#define _ANIMATION_MANAGER_
#include "animationpack.hpp"

typedef struct
{
	AnimationPack*	animationPack;
	std::string		fileName;
	int				use;
}AnimationId;

class AnimationManager
{
	private:
		static std::vector<AnimationId> mTable;
	public:
		static AnimationPack& load(const std::string& pAnimationPackName);
		static void unload(const std::string& pAnimationPackName);
		static void clear();
};

#endif
