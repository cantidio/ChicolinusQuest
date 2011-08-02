#ifndef _SPRITE_PACK_
#define _SPRITE_PACK_
#include "include.hpp"
#include "point.hpp"

class SpritePack
{
	protected:
		std::vector<ALLEGRO_BITMAP*> mSprites;
		Point mOffset;
		int where;
	public:
		SpritePack();
		SpritePack
		(
			const std::string&		pSpriteFile,
			const int&				pSpriteWidth,
			const int&				pSpriteHeight,
			const ALLEGRO_COLOR&	pAlpha
		);
		~SpritePack();
		int size() const;
		ALLEGRO_BITMAP* operator[](const unsigned int& pIndex) const;
};
#endif
