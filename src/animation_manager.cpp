#include "../include/animation_manager.hpp"

std::vector<AnimationId> AnimationManager::mTable;

AnimationPack& AnimationManager::load(const std::string& pAnimationPackName)
{
	unsigned int i;
	for(i = 0; i < mTable.size(); ++i)
	{
		if(mTable[i].fileName == pAnimationPackName)
		{
			++mTable[i].use;
			return *mTable[i].animationPack;
		}
	}
	AnimationId animationId;
	animationId.use             = 1;
	animationId.fileName        = pAnimationPackName;
	animationId.animationPack   = new AnimationPack(pAnimationPackName);
	mTable.push_back(animationId);
	return *animationId.animationPack;
}

void AnimationManager::unload(const std::string& pAnimationPackName)
{
	for(unsigned int i = 0; i < mTable.size(); ++i)
	{
		if(mTable[i].fileName == pAnimationPackName)
		{
			--mTable[i].use;
			if(mTable[i].use<=0)
			{
				delete mTable[i].animationPack;
				mTable.erase(mTable.begin()+i);
			}
			break;
		}
	}
}

void AnimationManager::clear()
{
	for(unsigned int i = 0; i < mTable.size(); ++i)
	{
		delete mTable[i].animationPack;
	}
	mTable.clear();
}

