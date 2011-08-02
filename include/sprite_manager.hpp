#ifndef _SPRITE_MANAGER_
#define _SPRITE_MANAGER_
#include "spritepack.hpp"

typedef struct
{
	SpritePack* spritePack;
	std::string fileName;
	int use;
}SpriteId;

class SpriteManager
{
	private:
		static std::vector<SpriteId> mTable;
	public:
		static SpritePack* load
		(
			const std::string&		pSpriteFile,
			const int&				pSpriteWidth,
			const int&				pSpriteHeight,
			const ALLEGRO_COLOR&	pAlpha
		);
		static void unload(const std::string& pSpritePackName);
		static void clear();
};

#endif

