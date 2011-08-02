#include "sprite_manager.hpp"

std::vector<SpriteId> SpriteManager::mTable;

SpritePack* SpriteManager::load
(
	const std::string&		pSpriteFile,
	const int&				pSpriteWidth,
	const int&				pSpriteHeight,
	const ALLEGRO_COLOR&	pAlpha
)
{
	for(unsigned int i = 0; i < mTable.size(); ++i)
	{
		if( mTable[i].fileName == pSpriteFile )
		{
			++mTable[i].use;
			return mTable[i].spritePack;
		}
	}

	SpriteId spriteId;
	spriteId.use        = 1;
	spriteId.fileName   = pSpriteFile;
	spriteId.spritePack = new SpritePack(pSpriteFile, pSpriteWidth, pSpriteHeight, pAlpha);


	mTable.push_back(spriteId);
	return spriteId.spritePack;
}

void SpriteManager::unload(const std::string& pSpritePackName)
{
	for(unsigned int i = 0; i < mTable.size(); ++i)
	{
		if(mTable[i].fileName == pSpritePackName)
		{
			--mTable[i].use;
			if(mTable[i].use <= 0)
			{
				delete mTable[i].spritePack;
				mTable.erase(mTable.begin() + i);
			}
			break;
		}
	}
}

void SpriteManager::clear()
{
	for(unsigned int i = 0; i < mTable.size(); ++i)
	{
		delete mTable[i].spritePack;
	}
	mTable.clear();
}
